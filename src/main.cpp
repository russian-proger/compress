#include "main.h"
#include "buffer.h"
#include "compressors/compressors.h"

using namespace cmp;

void print_help()
{
    printf("\033[1mUsage\033[0m: compress [OPTION]... FILE\n\n");
    printf("\033[1mArguments:\033[0m\n");
    printf("  -h\toutput help page\n");
    printf("  -x\textract mode\n");
    printf("  -o\toutput path\n");
    printf("  -v\toutput detail information\n");
    printf("  -m\tcompress via defined \033[4malgorithms:\033[0m\n");
    printf("\t\t1 - Huffman code\n");
    printf("\t\t2 - Arithmetic encoding\n");
    printf("\t\t3 - Burrows–Wheeler transform\n");
    printf("\t\t4 - Book stack\n\n");
}

int main(int argc, char **argv)
{
    std::string ipath = ""; // Path to input file
    std::string opath = ""; // Path to output file
    std::ifstream ifile;    // Input stream
    std::ofstream ofile;    // Output stream

    Buffer
        input_buffer,    // To read from ifile
        output_buffer;   // To write to  ofile

    // True if needed to extract compressed file
    bool extract_mode = false;

    // Sequence of numbers, indicating order of compress algorithm
    std::string algorithm_order = "4";

    // If true, program will be printing detail information
    bool vendor = false;

    // Reading arguments
    try {
        FLAG flag = FLAG::NONE;
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] == '-') {
                if (strlen(argv[i]) > 1)
                switch (argv[i][1]) {
                    // Help
                    case 'h':
                    {
                        print_help();
                        return 0;
                    }

                    // Extract (Default compress)
                    case 'x':
                    {
                        extract_mode = true;
                        break;
                    }

                    // Receiving algorithm order
                    case 'm':
                    {
                        flag = FLAG::ALGORITHM_ORDER;
                        break;
                    }

                    // Output path
                    case 'o':
                    {
                        flag = FLAG::OUTPUT_PATH;
                        break;
                    }

                    // Output details
                    case 'v':
                    {
                        vendor = true;
                        break;
                    }
                }
            }
            else {
                switch (flag) {
                    case FLAG::NONE:
                    {
                        // I/O File
                        ipath = argv[i];
                        break;
                    }

                    case FLAG::ALGORITHM_ORDER:
                    {
                        algorithm_order = argv[i];
                        break;
                    }

                    case FLAG::OUTPUT_PATH:
                    {
                        opath = argv[i];
                        break;
                    }
                }

                flag = FLAG::NONE;
            }
        }
    }
    catch (const std::exception &e) {
        printf("\033[1;31mError:\033[0m %s", e.what());
        return 0;
    }
    std::cout << "Algorithm: " << algorithm_order << "\n";

    if (ipath == "")
    {
        printf("\033[1;31mError:\033[0m No input file chosen\n");
        return 0;
    }

    if (!Exists(ipath))
    {
        printf("\033[1;31mError:\033[0m Input file doesn't exist\n");
        return 0;
    }

    if (opath == "")
    {
        opath = ipath.substr(0, ipath.find_last_of('.')) + ".cmp";
        if (vendor)
        {
            printf("\033[1;33mWarning:\033[0m no output file chosen so it's %s\n", opath.c_str());
        }
    }

    try {
        ifile.open(ipath, std::ios::binary);
    }
    catch (const std::exception &e) {
        printf("\033[1;31mError while reading:\033[0m %s", e.what());
        return 0;
    }
    if (!extract_mode)
    {
        // Encode mode
        input_buffer << Atomic::Make((byte)0);
        ifile >> input_buffer;
        ifile.close();



        Buffer buffer;

        for (char alg_code : algorithm_order) {
            int ind = (int)alg_code - '0';
            
            // Skip when trying to get plain compressor
            if (ind == 0) continue;

            if (ind <= compressors.size()) {
                // Applying compressor

                Compressor *compressor = compressors[ind];
                compressor->SetSource(&input_buffer);
                compressor->SetBuffer(&buffer);
                compressor->SetOutput(&output_buffer);

                output_buffer << Atomic::Make((byte)ind);

                compressor->Encode();

                std::swap(input_buffer, output_buffer);
                output_buffer.Clear();
            }
        }

        std::swap(input_buffer, output_buffer);
    }
    else {
        ifile >> input_buffer;
        ifile.close();

        Atomic atomic = Atomic::Make((byte)0);
        Buffer buffer;

        input_buffer >> atomic;

        while (*atomic.GetData() != 0) {
            std::cout << "ALgo: " << (int)*atomic.GetData() << "\n";
            assert(*atomic.GetData() <= compressors.size());

            Compressor *compressor = compressors[*atomic.GetData()];
            compressor->SetSource(&input_buffer);
            compressor->SetBuffer(&buffer);
            compressor->SetOutput(&output_buffer);

            compressor->Decode();

            std::swap(input_buffer, output_buffer);
            output_buffer.Clear();

            input_buffer >> atomic;
        }

        std::swap(input_buffer, output_buffer);
    }

    try {
        ofile.open(opath, std::ios::binary);
        ofile << output_buffer;
        ofile.close();
    }
    catch (const std::exception &e) {
        printf("\033[1;31mError while writing:\033[0m %s", e.what());
        return 0;
    }
}