import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMHITSHIFTER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_98_1_yUz.root'
   )
)

process.g4SimHits = cms.EDProducer("SimHitShifter",
   ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/goodtest.txt')
#  ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/noMap.txt')
#  ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/marcelloTEst/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/goodMap.txt')
)


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_SHIFT.root'),
    outputCommands = cms.untracked.vstring('keep *','keep *_g4SimHits_Muon*Hits_SIMHITSHIFTER','drop *_g4SimHits_Muon*Hits_HLT','drop *_simMuon*_*_*','drop CrossingFrame*_mix_*_*')
)
  
process.p = cms.Path(process.g4SimHits)

process.e = cms.EndPath(process.out)
