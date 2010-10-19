import FWCore.ParameterSet.Config as cms

theshifter = cms.EDProducer("SimHitShifter",
#  ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/goodtest.txt')
#  ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/noMap.txt')
   ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/goodMap.txt')
)

