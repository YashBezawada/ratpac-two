#ifndef __RATOutNtupleProc___
#define __RATOutNtupleProc___

#include <RAT/DS/Run.hh>
#include <RAT/Processor.hh>
#include <functional>

class TFile;
class TTree;

namespace RAT {

class OutNtupleProc : public Processor {
public:
  static int run_num;
  OutNtupleProc();
  virtual ~OutNtupleProc();

  // file - string, name of file to open for output, file will be erased
  // updatefile - string, name of file to append to
  // (do not use both file and update file)
  // virtual void SetS(std::string param, std::string value);

  // autosave - integer, update root file every N kilobytes
  // savetree 0 - Do not save the event tree.  Must set *before* file or
  // updatefile.
  // virtual void SetI(std::string param, int value);

  virtual Processor::Result DSEvent(DS::Root *ds);

  virtual bool OpenFile(std::string theFilename);

  virtual void SetI(std::string param, int value);
  virtual void SetS(std::string param, std::string value);

  // Exposed members for external tools
  DS::Run *runBranch;
  // Fill Functions
  std::vector<std::function<void()>> additionalBranches;
  struct NtupleOptions {
    bool tracking;
    bool mcparticles;
    bool pmthits;
    bool untriggered;
  };
  NtupleOptions options;

protected:
  std::string defaultFilename;
  TFile *outputFile;
  TTree *outputTree;
  TTree *metaTree;
  // Meta Branches
  Int_t runId;
  ULong64_t runType;
  TTimeStamp runTime;
  int dsentries;
  std::string macro;
  std::vector<int> pmtType;
  std::vector<int> pmtId;
  std::vector<double> pmtX;
  std::vector<double> pmtY;
  std::vector<double> pmtZ;
  std::vector<double> pmtU;
  std::vector<double> pmtV;
  std::vector<double> pmtW;
  // Data Branches
  double mcx, mcy, mcz;
  double mcu, mcv, mcw;
  double mcke;
  int evid;
  int subev;
  ULong64_t nanotime; // 584 years of data
  // MCParticles
  int mcpcount;
  std::vector<Int_t> pdgcodes;
  std::vector<double> mcKEnergies;
  std::vector<double> mcPosx;
  std::vector<double> mcPosy;
  std::vector<double> mcPosz;
  std::vector<double> mcDirx;
  std::vector<double> mcDiry;
  std::vector<double> mcDirz;
  // Reconstruted variables
  std::vector<int> fitterId;
  std::vector<double> fitx, fity, fitz;
  std::vector<double> fitu, fitv, fitw;
  // Store PMT Hit Positions
  std::vector<int> hitPMTID;
  std::vector<double> hitPMTTime;
  std::vector<double> hitPMTCharge;
  // Tracking
  std::map<std::string, int> processCodeMap;
  std::vector<int> processCodeIndex;
  std::vector<std::string> processName;

  std::vector<int> trackPDG;
  std::vector<std::vector<double>> trackPosX;
  std::vector<std::vector<double>> trackPosY;
  std::vector<std::vector<double>> trackPosZ;
  std::vector<std::vector<double>> trackMomX;
  std::vector<std::vector<double>> trackMomY;
  std::vector<std::vector<double>> trackMomZ;
  std::vector<std::vector<double>> trackKE;
  std::vector<std::vector<double>> trackTime;
  std::vector<std::vector<int>> trackProcess;
};

} // namespace RAT

#endif