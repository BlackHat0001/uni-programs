#include <iostream>

class Pixel {
    public:
        float xCoord;
        float yCoord;
        unsigned int brightness;

        Pixel(float xCoord, float yCoord, int brightness) {
            this->xCoord = xCoord;
            this->yCoord = yCoord;
            this->brightness = brightness;
        }


        void showPixelDetail() const {
            std::cout << "Pixel Detail: (x: " << xCoord << ", y: " << yCoord << ", brightness: " << brightness << ")\n";
        }
};

class Icon {
    private:
        Pixel* iconPixels[16];

    public:
        int id;
        explicit Icon(int id);
        ~Icon();

        void setPixel(int index, Pixel px) {
            iconPixels[index] = new Pixel(px);
        }

        Pixel* getPixel(int index) {
            return iconPixels[index];
        }

        void showIconDetail() const {
            std::cout << "Details of Icon ID: " << id << "\n";
            for (int i = 0; i < 16; i++) {
                std::cout << "| Pixel " << i+1 << "/16 | ";
                iconPixels[i]->showPixelDetail();
            }
        }
};

Icon::Icon(int id) : id(id), iconPixels() {
    for (int i = 0; i < 16; ++i) {
        iconPixels[i] = new Pixel(0.0f, 0.0f, 0);
    }
}

Icon::~Icon(){
    delete[] &iconPixels;
};

class RadarDisplay {

    private:
        Icon* radarIcons[100];
        int numberOfActiveIcons;

    public:
        RadarDisplay();

        void addIcon(Icon* iconToSet) {
            if(numberOfActiveIcons >= 100) {
                std::cout << "Error in addIcon in RadarDisplay: Max number of icons reached";
                return;
            }
            for (int i = 0; i < 100; ++i) {
                if(radarIcons[i] == nullptr) {
                    radarIcons[i] = iconToSet;
                    numberOfActiveIcons++;
                    std::cout << "Added icon in RadarDisplay ID: " << iconToSet->id << "\n";
                    return;
                }
            }
        }

        void removeIcon(Icon* iconToRemove) {
            for (int i = 0; i < 100; ++i) {
                if(radarIcons[i] != nullptr && radarIcons[i]->id == iconToRemove->id) {
                    std::cout << "Deleted icon in RadarDisplay ID: " << radarIcons[i]->id << "\n";
                    radarIcons[i] = nullptr;
                    numberOfActiveIcons--;
                    return;
                }
            }
            std::cout << "Error in removeIcon in RadarDisplay: Icon not found\n";
        }

        Icon* getIcon(Icon* iconSearch) {
            for (int i = 0; i < 100; ++i) {
                if(radarIcons[i] != nullptr && radarIcons[i]->id == iconSearch->id) {
                    return radarIcons[i];
                }
            }
            std::cout << "Error in getIcon in RadarDisplay: Icon not found\n";
            return nullptr;
        }

        void showRadarDetail() {
            for (int i = 0; i < 100; ++i) {
                if(radarIcons[i] != nullptr) {
                    std::cout << "Icon ID: " << radarIcons[i]->id << " at Element: " << i << "\n";
                }
            }
        }
};

RadarDisplay::RadarDisplay() : numberOfActiveIcons(0), radarIcons() {
}

void createDiagonalLine(Icon* icon) {
    for (int i = 0; i < 16; i++) {
        Pixel newPx(i+1, i+1, 15);
        icon->setPixel(i, newPx);
    }
}

Icon* initPlane(Icon* icon) {
    return new Icon(0);
}
Icon* initHelicopter(Icon* icon) {
    return new Icon(1);
}
Icon* initSpaceship(Icon* icon) {
    return new Icon(2);
}

int main()
{

    Pixel aPixel(3.9f, 4.1f, 7);
    std::cout << "var aPixel | x: " << aPixel.xCoord << " y: " << aPixel.yCoord << " brightness: " << aPixel.brightness<<"\n";

    aPixel.showPixelDetail();

    Icon myIcon(1);
    Pixel pixelOne(2, 5, 20);
    myIcon.setPixel(0, pixelOne);

    Icon diagonalLine(7);
    createDiagonalLine(&diagonalLine);
    diagonalLine.showIconDetail();

    Icon* allIcons[500];
    allIcons[0] = initPlane(*allIcons + 0);
    allIcons[1] = initHelicopter(*allIcons + 1);
    allIcons[2] = initSpaceship(*allIcons + 2);

    RadarDisplay radar;
    radar.addIcon(allIcons[0]);
    radar.addIcon(allIcons[1]);
    radar.addIcon(allIcons[2]);

    radar.showRadarDetail();

    radar.removeIcon(allIcons[2]);

    radar.showRadarDetail();

}