/*
* -------- Radar Display Project ---------
* A program to demonstrate the use of Object Orientated Programming paradigms and how they are useful in various applications
* Here, it is implemented for a radar display to provide better data control over the rendering
*
* Code is INCITS PL22.16 C++ compliant and is to be run under CodeBlocks / CLion
*
* Dependencies: iostream - For logging/printing purposes using std::cout
*
* Copyright Daniel Marcovecchio
* @author https://github.com/BlackHat0001
*
* enough comments to write a novel?!
*/

/*
 ---- TEST DATA ----

 All test data is pre-written in the main implementation of this program

 It would be worthwhile to test if the RadarDisplay can accept more than 100 Icons or not

 -------------------
*/

//------ Includes
#include <iostream>

//------ Program Configs
const unsigned int radarDisplayMaxIcons = 100;
const unsigned int iconPixelsNumber = 16;

//------ Declarations

/** Class Pixel
 * Pixel is a class to encapsulate data for each pixel used during rendering
 * @property xCoord and yCoord which are floats to store pixel x and y position
 * @property brightness which is a uint in range of 0 to 20
 *
 * @author Daniel Marcovecchio
 */
class Pixel;

/** Class Icon
 * Icon is a class to represent each Icon on the display. Each icon is comprised of 16 Pixels (making up a 4x4 grid)
 * @property iconPixels which is a pointer to an array of Pixel objects
 * @property id unique integer identifier for this Icon
 *
 * @author Daniel Marcovecchio
 */
class Icon;

/** Class RadarDisplay
 * RadarDisplay is a class for managing the display of many Icons
 * It has a pointer to an array of Icons currently used on the display
 * Also has multiple functions for the adding and removing of Icons on the Display
 *
 * @property radarIcons which is a pointer to an array of Icon objects
 * @property numberOfActiveIcons the number of active icons on the display right now
 *
 * @author Daniel Marcovecchio
 */
class RadarDisplay;

/** Method initialiseAsDefaultDiagonalLine
 * initialiseAsDefaultDiagonalLine is a method to populate an Icon with the pixel data for a diagonal line
 *
 * @param icon the Icon object in order to populate the 16 pixel values into
 *
 * @author Daniel Marcovecchio
 */
void initialiseAsDefaultDiagonalLine(Icon* icon);

/** init{Vehicle} Methods
 * These methods initialize an Icon object for various vehicle types, setting up and populating necessary pixel data
 *
 * @return *Icon
 *
 * @author Daniel Marcovecchio
 */
Icon* initPlane();
Icon* initHelicopter();
Icon* initSpaceship();


//------ Code body

class Pixel {
    // Pixel class to encapsulate pixel data

    // We want our pixel data public, as there is no issue with other parts of the program writing and reading it
    // in-fact, we want to encourage this for our pixel data
    public:
        // Define our xCoord, yCoord and brightness
        float xCoord;
        float yCoord;
        unsigned int brightness;

        // Create a constructor for pixel, as it allows us to input all the data in one go
        // Constructor is defined in the class as this class is likely to be future-proof, and won't need an alternate implementation
        Pixel(float xCoord, float yCoord, int brightness) {
            // Set respective values from input parameters
            // For the coords, if they are less than zero, then default these to zero. Should be >= 0
            this->xCoord = xCoord >= 0 ? xCoord : 0;
            this->yCoord = yCoord >= 0 ? yCoord : 0;
            // For the brightness, default to zero if out of range for 0<=brightness<=20
            this->brightness = brightness >= 0 && brightness <= 20 ? brightness : 0;

            // Display respective error/warning messages if supplied values were out of range
            if(xCoord < 0 || yCoord < 0) {
                std::cout << "Error in Pixel Constructor: X or Y coord was less than zero, value defaulted to zero\n";
            } 
            if(brightness < 0 || brightness > 20) {
                std::cout << "Error in Pixel Constructor: brightness param was out of range 0<=brightness<=20, value was defaulted to zero\n";
            }
        }
        // Here we define the constructor to default behaviour operation as we don't have any memory we need to free up
        ~Pixel() = default;

        /** showPixelDetail
        * showPixelDetail is a method to log current pixel data
        * this method has its implementation elsewhere
        *
        * @author Daniel Marcovecchio
        */
        void showPixelDetail() const;
};

void Pixel::showPixelDetail() const {
    // Here is the implementation of the showPixelDetail function, to display current pixel data

    // Simply we output the xCoord, yCoord and brightness in a reasonable format
    std::cout << "Pixel Detail: (x: " << xCoord << ", y: " << yCoord << ", brightness: " << brightness << ")\n";
}

class Icon {
    //Class Icon to contain pixel data about an icon/image to be used on the display

    // Here is the private data
    private:
        // Here I define iconPixels as a pointer to a Pixel Array
        // This is specified as private as it is not necessary to have other parts of the program access this variable,
        // as I have instead used various setter and getter methods to directly control this.
        // This private implementation is future proofed and robust
        Pixel* iconPixels[iconPixelsNumber];

    // Here is the public data for this class
    public:
        // Definition of id, the integer identifier for each Icon object instance.
        // This is public so can be easily edited and accessed by other areas of the program, as intended
        int id;

        /** Constructor Icon
         * Define for the Constructor of this class
         * This is called when we want to make a instantiate an Icon object
         *
         * @param id the unique integer identifier of this Icon
         *
         * @author Daniel Marcovecchio
         */
        explicit Icon(int id);

        /** Destructor Icon
         * Define for the Destructor of this class
         * This is called once this object is no longer in use, and is to be deleted
         *
         * @author Daniel Marcovecchio
         */
        ~Icon();

        /** Method setPixel
         * Method to set one of the member pixels of this Icon, given by the index of said pixel
         *
         * @param index of the pixel in the iconPixels array
         * @param px the new pixel to replace the old one
         *
         * @author Daniel Marcovecchio
         */
        void setPixel(int index, Pixel px) {
            // Check if the parameter index is within the correct range, else through an error and return
            if(index < 0 || index > iconPixelsNumber-1) {
                std::cout << "Error in setPixel in Icon class: index out of array range\n";
                return;
            }
            // Create a new reference to the given Pixel
            // else, the value will lose its scope and will risk pointing to the wrong address
            // As the Pixel parameter is a copy of the pixel, WE CAN ASSUME THAT THIS IS DEFINED AND IT IS NOT NULLPTR
            iconPixels[index] = new Pixel(px);
        }

        /** Method getPixel
         * Method to return a pixel from the member pixel array iconPixels
         * Currently not used in code, however exists for future expansion if required
         *
         * @param index of the pixel in the iconPixels array to return
         *
         * @author Daniel Marcovecchio
         */
        Pixel* getPixel(int index) {
            // Check if the parameter index is within the correct range, else through an error and return nullptr
            if(index < 0 || index > iconPixelsNumber-1) {
                std::cout << "Error in setPixel in Icon class: index out of array range\n";
                return nullptr;
            }
            // Return the reference to the pixel at the index parameter
            return iconPixels[index];
        }

        /** showIconDetail
        * showIconDetail is a method to log current Icon data
        * Recommended implementation is to loop for all member pixels and call showPixelDetail, to get pixel details
        *
        * @author Daniel Marcovecchio
        */
        void showIconDetail() const;
};

Icon::Icon(int id) : id(id), iconPixels() {
    // Implementation of the Icon constructor
    // This constructor makes use of Constructor Initializers to automatically assign variables

    // Loop to populate member pixel array iconPixels with empty pixels, this avoids future nullptr errors
    for (int i = 0; i < iconPixelsNumber; ++i) {
        iconPixels[i] = new Pixel(0.0f, 0.0f, 0);
    }
}

Icon::~Icon(){
    // Implementation of Icon destructor

    // Dynamically delete (clear) memory allocated to iconPixels array
    delete[] &iconPixels;
}

void Icon::showIconDetail() const {
    // Implementation of showIconDetail

    // First display the current ID of this icon, for logging purposes
    std::cout << "Details of Icon ID: " << id << "\n";
    // Now loop for all member pixels (iconPixels) and invoke the iconPixelsNumber method for each one to display the respective pixel data
    for (int i = 0; i < iconPixelsNumber; i++) {
        std::cout << "| Pixel " << i+1 << "/" << iconPixelsNumber << " | ";
        // Check this pixel object is not empty before attempting to access its data
        if(iconPixels[i] != nullptr)
            iconPixels[i]->showPixelDetail();
    }
}

class RadarDisplay {
    // Radar display class managing child icons for a display instance

    // Private variables define
    private:
        // radarIcons is a pointer to an array of Icons, of length radarDisplayMaxIcons, default max length 100
        // This is kept private as add and remove type methods have been created to control the functionality
        Icon* radarIcons[radarDisplayMaxIcons];
        // The number of active icons in use, also kept private for the same reason
        int numberOfActiveIcons;

    // Public variables define
    public:
        // Define of the constructor and destructor for RadarDisplay
        RadarDisplay();
        ~RadarDisplay();

        /** Method addIcon
         * Method to add an Icon reference to the current list of active icons
         * Finds a free space in the array and inserts into that element
         *
         * @param iconToSet the icon to add to the radarIcons list
         *
         * @author Daniel Marcovecchio
         */
        void addIcon(Icon* iconToSet) {
            // First check if there is space in the array to add another Icon element, by comparing numberOfActiveIcons
            // return if not
            if(numberOfActiveIcons >= radarDisplayMaxIcons) {
                std::cout << "Error in addIcon in RadarDisplay: Max number of icons reached";
                return;
            }
            // Loop for all child Icons
            for (int i = 0; i < radarDisplayMaxIcons; ++i) {
                // If a nullptr is found, then the element is empty, so instert into here
                if(radarIcons[i] == nullptr) {
                    // Insert into current element
                    radarIcons[i] = iconToSet;
                    // Increment the number of active icons, as we have added one
                    numberOfActiveIcons++;
                    std::cout << "Added icon in RadarDisplay ID: " << iconToSet->id << "\n";
                    return;
                }
            }
        }

        /** Method removeIcon
         * Method to remove an Icon from the current list of active icons
         * Searches whole array, comparing Icon ID's, and removes matching one
         *
         * @param iconToRemove the icon to remove from the radarIcons list
         *
         * @author Daniel Marcovecchio
         */
        void removeIcon(Icon* iconToRemove) {
            // First check if the array is already empty or not before attempting, if it is, return
            if(numberOfActiveIcons < 1) {
                std::cout << "Error in addIcon in RadarDisplay: Array already empty";
                return;
            }
            // Loop for all child Icons
            for (int i = 0; i < radarDisplayMaxIcons; ++i) {
                // Check that the current Icon is not empty before attempting to read its ID
                // Then check if the ID matches the search case ID
                if(radarIcons[i] != nullptr && radarIcons[i]->id == iconToRemove->id) {
                    std::cout << "Deleted icon in RadarDisplay ID: " << radarIcons[i]->id << "\n";
                    // If a match is found, set the array element back to nullptr, therefore its deleted
                    radarIcons[i] = nullptr;
                    // Reduce the number of active icons by one
                    numberOfActiveIcons--;
                    return;
                }
            }
            std::cout << "Error in removeIcon in RadarDisplay: Icon not found\n";
        }
        /** Method showRadarDetail
         * Method to display all current radar child Icons
         *
         * @author Daniel Marcovecchio
         */
        void showRadarDetail() const;
};

RadarDisplay::RadarDisplay() : numberOfActiveIcons(0), radarIcons() {}

RadarDisplay::~RadarDisplay() {
    // The destructor for RadarDisplay

    //When the current display is destroyed, free up the momory allocated to the radarIcons array
    delete[] &radarIcons;
}

void RadarDisplay::showRadarDetail() const {
    // showRadarDetail to display all current radar child Icons

    // Loop for the whole Icon array, even empty ones
    for (int i = 0; i < radarDisplayMaxIcons; ++i) {
        // If an element is not empty, then print its iconID and array element index
        if (radarIcons[i] != nullptr) {
            std::cout << "Icon ID: " << radarIcons[i]->id << " at Element: " << i << "\n";
        }
    }
}



void initialiseAsDefaultDiagonalLine(Icon* icon) {
    // initialiseAsDefaultDiagonalLine Function takes a icon pointer and populates it with pixel data of a diagonal line, of brightness 15

    // Loop for all pixel slots, iconPixelsNumber, default 16
    for (int i = 0; i < iconPixelsNumber; i++) {
        // Create a new Pixel object with xCoord and yCoord equal to i+1
        // And brightness level of 15
        // Sample data would look like:
        // 1,1,15  2,2,15  3,3,15  4,4,15 etc
        Pixel newPx((float) i+1, (float) i+1, 15);
        // Use the setPixel function on the Icon class to update the pixel for the current index
        icon->setPixel(i, newPx);
    }
}

Icon* initPlane() {
    // Initialize and return a Plane of ID 0
    return new Icon(0);
}
Icon* initHelicopter() {
    // Initialize and return a Helicopter of ID 1
    return new Icon(1);
}
Icon* initSpaceship() {
    // Initialize and return a Helicopter of ID 2
    return new Icon(2);
}

/** main method
* main implementation for testing the different OOP implementations in this program
* All test data is pre-written/hardcoded, as required in the subtasks
*
* @author Daniel Marcovecchio
*/
int main()
{
    std::cout << "------------- Radar Display Project ---------------\n";

    std::cout << "----- Displaying pixel data of aPixel -----\n";
    // -- SUB TASK - DISPLAY aPixel
    // Create a new pixel
    Pixel aPixel(3.9f, 4.1f, 7);
    std::cout << "aPixel | (x: " << aPixel.xCoord << " y: " << aPixel.yCoord << " brightness: " << aPixel.brightness<<")\n";
    // --

    std::cout << "\n----- Now displaying aPixel data using showPixelDetail() -----\n";

    // -- SUB TASK - Using showPixelDetail to display pixel details
    aPixel.showPixelDetail();
    // --

    // -- SUB TASK - Create a icon and pixel, and set pixel as first pixel in the icon
    Icon myIcon(1);
    Pixel pixelOne(2, 5, 20);
    myIcon.setPixel(0, pixelOne);
    // --

    std::cout << "\n----- Diagonal Line data test result -----\n";

    // -- SUB TASK - Using initialiseAsDefaultDiagonalLine to create a diagonal line in an Icon, and display this using showIconDetail
    // Create a icon to use, with id 7
    Icon diagonalLine(7);
    // Pass this into the diagonalLine function to populate the respective pixel data. Note it is passed as a pointer
    initialiseAsDefaultDiagonalLine(&diagonalLine);
    // Log the icon detail of this Icon
    diagonalLine.showIconDetail();
    // --

    std::cout << "\n----- Radar Display Testing -----\n";

    // -- SUB TASK - Implementation & Testing of the Top-Level RadarDisplay
    // Define the list of all icons. This is 500 big to represent maybe all kinds of objects. E.g. Red planes, blue planes, green UFO's
    Icon* allIcons[500];
    // Initialize some array elements for different types of vehicles
    allIcons[0] = initPlane();
    allIcons[1] = initHelicopter();
    allIcons[2] = initSpaceship();

    // Define our RadarDisplay object, that manages the top-level display
    RadarDisplay radar;
    // Add our Vehicle objects to this radar instance
    radar.addIcon(allIcons[0]);
    radar.addIcon(allIcons[1]);
    radar.addIcon(allIcons[2]);

    // Show the radar details, as we can see in the console, all three Icon ID's are present
    radar.showRadarDetail();

    // Now lets try removing the one with ID one
    radar.removeIcon(allIcons[1]);

    // As we display it again, we can see that now this one is removed from the list of active Icons
    radar.showRadarDetail();

    // ------- END

    // We're done! :D

}