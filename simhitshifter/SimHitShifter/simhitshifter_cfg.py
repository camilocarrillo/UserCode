import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/HSCPstau_M-200_7TeV-pythia6_CMSSW_358patch2.root'
#      'file:/tmp/carrillo/PYTHIA6_Exotica_HSCP_stau200_cfg_py_GEN_SIM_SHIFT_DIGI_L1_DIGI2RAW_HLT.root'
   )
)

process.g4SimHits = cms.EDProducer("SimHitShifter",
ShiftFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/simhits/testFromScratch/CMSSW_3_5_8_patch2/src/simhitshifter/SimHitShifter/Merged_Muon_RawId_Shift.txt') 
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/myOutputFile.root')
)

  
process.p = cms.Path(process.g4SimHits)

process.e = cms.EndPath(process.out)
