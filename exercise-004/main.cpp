#include <fmt/core.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

// Header wird von CMake generiert.
// Enthält:
//   const unsigned char image[];
//   const unsigned int  image_width;
//   const unsigned int  image_height;
#include "embedded_image.h"

int main()
{
    // 1. Größe des Arrays bestimmen
    // Wir wissen: 3 Kanäle (RGB), also:
    const std::size_t pixel_count = static_cast<std::size_t>(image_width) *
                                    static_cast<std::size_t>(image_height);
    const std::size_t expected_size = pixel_count * 3; // RGB

    fmt::print("Embedded RGB image: {}x{} pixels\n", image_width, image_height);
    fmt::print("Expected data size (width*height*3): {} bytes\n", expected_size);

    // Das Array hat exakt diese Größe (weil du img.tobytes() benutzt hast)
    // wir können aber nicht sizeof(image) in diesem File bestimmen,
    // weil 'image' hier ein externes Symbol aus dem Header ist (kein static array).
    // -> Wir vertrauen auf den Generator.

    // 2. cv::Mat aus den rohen RGB-Daten bauen
    // OpenCV erwartet BGR, aber für reine Parameterabfrage ist das egal.
    cv::Mat img(
        static_cast<int>(image_height),
        static_cast<int>(image_width),
        CV_8UC3,
        const_cast<unsigned char*>(image) // Daten werden nicht verändert
    );

    if (img.empty()) {
        fmt::print("Error: constructed cv::Mat is empty.\n");
        return 1;
    }

    fmt::print("cv::Mat info:\n");
    fmt::print("  rows     = {}\n", img.rows);
    fmt::print("  cols     = {}\n", img.cols);
    fmt::print("  channels = {}\n", img.channels());
    fmt::print("  type     = {}\n", img.type());

    // Wenn du sicher sein willst, dass niemand die eingebetteten Daten verändert:
    cv::Mat img_copy = img.clone();
    fmt::print("Cloned image size: {} x {}, channels: {}\n",
               img_copy.cols, img_copy.rows, img_copy.channels());

    return 0;
}
