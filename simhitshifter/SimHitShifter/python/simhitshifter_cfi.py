import FWCore.ParameterSet.Config as cms

theshifter = cms.EDProducer("SimHitShifter",
  ShiftFileName =cms.untracked.string('~/simhits/testFromScratch/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/Merged_Muon_RawId_Shift.txt')
)

