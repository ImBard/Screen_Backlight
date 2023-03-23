#include <iostream>
#include <Windows.h>
#include <bitset> // Biblioteca necessária para converter as cores para binário

class Colors {
public:
    COLORREF xUp, xDown, yLeft, yRight;

    Colors(COLORREF xUp, COLORREF xDown, COLORREF yLeft, COLORREF yRight) {
        this->xUp = xUp;
        this->xDown = xDown;
        this->yLeft = yLeft;
        this->yRight = yRight;
    }

    int* getRGB(COLORREF color) const {
        int red = GetRValue(color);
        int green = GetGValue(color);
        int blue = GetBValue(color);

        int rgb[3] = {red,green,blue};
        return rgb;
    }

    void stdColors() const {
        COLORREF color = 5507151; // Valor RGB inteiro
        int red = GetRValue(color); // Componente vermelho (R)
        int green = GetGValue(color); // Componente verde (G)
        int blue = GetBValue(color); // Componente azul (B)

        std::cout << "R: " << red << "\n";
        std::cout << "G: " << green << "\n";
        std::cout << "B: " << blue << "\n";
    }


};

Colors getColors() {
    // Obtém o handle da tela
    HWND desktop = GetDesktopWindow();

    // Obtém a largura e altura da tela
    RECT desktopRect;
    GetWindowRect(desktop, &desktopRect);
    int screen_width = desktopRect.right - desktopRect.left;
    int screen_height = desktopRect.bottom - desktopRect.top;

    // Captura as cores das bordas da tela
    COLORREF xUp = GetPixel(GetDC(desktop), 0, 0);
    COLORREF xDown = GetPixel(GetDC(desktop), screen_width - 1, screen_height - 1);
    COLORREF yLeft = GetPixel(GetDC(desktop), 0, screen_height - 1);
    COLORREF yRight = GetPixel(GetDC(desktop), screen_width - 1, 0);

    return Colors(xUp, xDown, yLeft, yRight);
}

int main() {
    while (true) {
        Colors colors = getColors();
        std::cout << "xUp: " << std::bitset<24>(colors.xUp) << "\n";
        std::cout << "xDown: " << std::bitset<24>(colors.xDown) << "\n";
        std::cout << "yLeft: " << std::bitset<24>(colors.yLeft) << "\n";
        std::cout << "yRight: " << std::bitset<24>(colors.yRight) << "\n";
//        colors.stdColors();
        Sleep(500); // Espera 1 segundo antes de capturar as cores novamente
    }

    return 0;
}