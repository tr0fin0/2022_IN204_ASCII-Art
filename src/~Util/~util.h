#include <iostream>
#include <zlib.h>
#include <cairo/cairo.h>
#include <string>

#include <cairo.h>
#include <string>

void saveASCIIArtAsImage(const std::string& asciiArt, int widthInChars, int heightInChars, int outputWidth, int outputHeight, const std::string& outputImagePath)
{
    // Calcula a largura e a altura de cada caractere na imagem final
    int charWidth = outputWidth / widthInChars;
    int charHeight = outputHeight / heightInChars;

    // Cria uma superfície Cairo para a imagem final
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, outputWidth, outputHeight);

    // Cria um contexto Cairo para a superfície
    cairo_t* cr = cairo_create(surface);

    // Define a cor de preenchimento como preto
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_paint(cr);

    // Define o preenchimento da imagem como branco
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);

    // Define a fonte e o tamanho da fonte para os caracteres
    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, charHeight);

    // Desenha cada caractere na imagem
    for (int i = 0; i < asciiArt.size(); i++) {
        // Calcula a posição do caractere na imagem
        int x = i % widthInChars;
        int y = i / widthInChars;
        double xPos = x * charWidth;
        double yPos = y * charHeight;

        // Desenha o caractere na imagem
        cairo_move_to(cr, xPos, yPos);
        std::string character = asciiArt.substr(i, 1);
        cairo_show_text(cr, character.c_str());
    }

    // Salva o contexto Cairo como uma imagem em um arquivo PNG
    cairo_surface_write_to_png(surface, outputImagePath.c_str());

    // Libera a memória da superfície e do contexto Cairo
    cairo_surface_destroy(surface);
    cairo_destroy(cr);
}

std::string getFileName(const std::string& path)
{
    // Encontra a última ocorrência do separador de diretório na string do caminho
    size_t lastSeparator = path.find_last_of("/\\");
    // Se o separador não for encontrado, retorna o caminho completo
    if (lastSeparator == std::string::npos) {
        return path;
    }
    // Retorna a substring após o último separador de diretório
    return path.substr(lastSeparator + 1);
}

std::string generateNewFileLocation(const std::string& path){
    std::string fileName = getFileName(path);

    return path.substr(0, path.size() - fileName.size()) + "ASCII_" + fileName;
}

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


std::string getWaiting(){
    return 
"\n\n\n\n\n\n\n\n\n\n\n\n\n"
"           __    __   ____  ____  ______  ____  ____    ____         \n"
"          |  |__|  | /    ||    ||      ||    ||    \\  /    |        \n"
"          |  |  |  ||  o  | |  | |      | |  | |  _  ||   __|         \n"
"          |  |  |  ||     | |  | |_|  |_| |  | |  |  ||  |  |         \n"
"          |  `  '  ||  _  | |  |   |  |   |  | |  |  ||  |_ |         \n"
"           \\      / |  |  | |  |   |  |   |  | |  |  ||     |        \n"
"            \\_/\\_/  |__|__||____|  |__|  |____||__|__||___,_|       \n"
"                                                                      \n"
"             _____   ___   ____       ______  __ __    ___            \n"
"            |     | /   \\ |    \\     |      ||  |  |  /  _]        \n"
"            |   __||     ||  D  )    |      ||  |  | /  [_        \n"
"            |  |_  |  O  ||    /     |_|  |_||  _  ||    _]       \n"
"            |   _] |     ||    \\       |  |  |  |  ||   [_        \n"
"            |  |   |     ||  .  \\      |  |  |  |  ||     |       \n"
"            |__|    \\___/ |__|\\_|      |__|  |__|__||_____|       \n"
"                                                                        \n"
"                      ____  __ __    ___   _____ ______                 \n"
"                     /    ||  |  |  /  _] / ___/|      |                \n"
"                    |   __||  |  | /  [_ (   \\_ |      |              \n"
"                    |  |  ||  |  ||    _] \\__  ||_|  |_|              \n"
"                    |  |_ ||  :  ||   [_  /  \\ |  |  |                \n"
"                    |     ||     ||     | \\    |  |  |                \n"
"                    |___,_| \\__,_||_____|  \\___|  |__|                \n";}