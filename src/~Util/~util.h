#include <iostream>
#include <zlib.h>

void run(){
    std::cout <<"\x1b[32m\x1b[1m" << "___________________________________________________________________________\n";
    std::cout << std::endl;
    std::cout <<"                                               88                          \n";
    std::cout <<"                                               ""                          \n";
    std::cout <<"\n";
    std::cout <<"8b,dPPYba, 88       88 8b,dPPYba,  8b,dPPYba,  88 8b,dPPYba,   ,adPPYb,d8  \n";
    std::cout <<"88P\'   \"Y8 88       88 88P\'   `\"8a 88P\'   `\"8a 88 88P\'   `\"8a a8\"    `Y88  \n";
    std::cout <<"88         88       88 88       88 88       88 88 88       88 8b       88  \n";
    std::cout <<"88         \"8a,   ,a88 88       88 88       88 88 88       88 \"8a,   ,d88  \n";
    std::cout <<"88          `\"YbbdP'Y8 88       88 88       88 88 88       88  `\"YbbdP\"Y8  \n";
    std::cout <<"                                                               aa,    ,88  \n";
    std::cout <<"                                                                \"Y8bbdP\"   \n";
    std::cout <<"___________________________________________________________________________\n" << "\x1b[0m";
}   

std::string compress_string(const std::string& str) {
    // Definir o nível de compressão
    int level = Z_BEST_COMPRESSION;

    // Configurar o buffer de saída
    uLong compressed_size = compressBound(str.size());

    std::string compressed(compressed_size, 0);

    // Comprimir a string
    int result = compress((Bytef*)compressed.data(), &compressed_size, (const Bytef*)str.data(), str.size());

    // Verificar se houve erros
    if (result != Z_OK) {
        return "";
    }

    // Redimensionar o buffer de saída para o tamanho real da string comprimida
    compressed.resize(compressed_size);
    return compressed;
}

std::string decompress_string(const std::string& compressed_str) {
    // Configurar o buffer de saída
    uLong uncompressed_size = compressed_str.size() * 2;
    std::string uncompressed(uncompressed_size, 0);

    // Descomprimir a string
    int result = uncompress((Bytef*)uncompressed.data(), &uncompressed_size, (const Bytef*)compressed_str.data(), compressed_str.size());

    // Verificar se houve erros
    if (result != Z_OK) {
        return "";
    }

    // Redimensionar o buffer de saída para o tamanho real da string descomprimida
    uncompressed.resize(uncompressed_size);

    return uncompressed;
}
