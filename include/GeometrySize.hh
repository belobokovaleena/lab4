#ifndef GEOMETRYSIZE_HH
#define GEOMETRYSIZE_HH

#include <G4SystemOfUnits.hh>

//Размеры детектора
const double detector_side_size = 0.5 * meter;
const double detector_length = 2 * meter;

//Размеры калориметра
const double calorimeter_lead_thickness = 1 * cm;
const double calorimeter_plastic_thickness = 5 * cm;
//Число сегментов калориметра
const int calorimeter_number_of_segment = 8;

// Число ячеек трекового детектора в одном ряду
const int number_of_tracking_cell = 10;
// Полное число ячеек трекового детектора в одном слое
const int full_number_of_tracking_cell = number_of_tracking_cell * number_of_tracking_cell;
// Размеры трекового детектора
const double tracking_cell_size = 0.05 * meter;
const double tracking_thickness = 0.5 * mm;
// Растояния в трековом детекторе
const double distance_tracking_layer = 0.10 * meter;
const double distance_tracking_area = 0.20 * meter;
const double distance_tracking_center = 0.20 * meter;
const double distance_tracking_calorimeter = 0.10 * meter;

#endif //GEOMETRYSIZE_HH
