import FWCore.ParameterSet.Config as cms

g4SimHits = cms.EDProducer("SimHitShifter",
#  ShiftFileName = cms.untracked.string('../data/goodtest.txt')
#  ShiftFileName = cms.untracked.string('../data/noMap.txt')
#  ShiftFileName = cms.untracked.string('../data/goodMap.txt')
#  ShiftFileName = cms.untracked.string('../data/2011Map.txt')
   ShiftFileName = cms.untracked.string('../data/2011_2Map.txt')
)

