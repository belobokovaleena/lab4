#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>
#include <G4MagneticField.hh>
#include <G4UniformMagField.hh>
#include <G4FieldManager.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include <G4SystemOfUnits.hh>

#include "GeometrySize.hh"
#include "CalorimeterSensitiveDetector.hh"
#include "TupleID.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction{
public:
    MyDetectorConstruction(TupleID *tupleID);
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();
    virtual void ConstructSDandField();

private:
    G4Material* vacuum;
    G4Material* lead;
    G4Material* plastic;
    G4Material *silicon;

    G4LogicalVolume *detectorLogic;
    G4LogicalVolume *magnetLogic;
    G4LogicalVolume *plasticLogic;
    G4LogicalVolume *siliconLogic;

    TupleID *tupleID;

    G4LogicalVolume* CreateDetector();
    G4LogicalVolume* CreateCalorimeterSection();

    G4LogicalVolume *createTrackingLayer();
    G4LogicalVolume *createTrackingSection();

    G4LogicalVolume *createMagnet();

    void setupDetectors();

    void defineMaterials();

};


#endif //DETECTORCONSTRUCTION_HH