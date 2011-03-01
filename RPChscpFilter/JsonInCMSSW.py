import FWCore.ParameterSet.Config as cms

process = cms.Process("ReSelRPChscpEvents")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.selRPC = cms.EDFilter("RPChscpFilter",
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rpcRecHits = cms.InputTag("rpcRecHits"),
   MinRPCRecHits = cms.untracked.int32(2), #Hits in tracker track
   rootFileNameCal = cms.untracked.string('/afs/cern.ch/user/c/carrillo/tesis/CMSSW_3_8_4_patch4/src/MuonRPCMonitor/MuonRPCMonitor/hscp.root'),
   synchth = cms.untracked.double(0.02), #percentage of RPCRecHIts outside bx=0
   minIntegral = cms.untracked.double(20), #minimum number of hits asociated to a track in order to say something about the efficiency
   minMean = cms.untracked.double(0.02)
)

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('/store/data/Run2010B/Mu/RECO/PromptReco-v2/000/146/804/5AF410C9-F8CA-DF11-8486-0030487D05B0.root')
#  fileNames = cms.untracked.vstring('file:/tmp/carrillo/filtering.root')
)

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
        '146804:111-146804:148',
        '146804:150-146804:520',
        '146804:522-146804:789',
        '146804:791-146804:822',
        '146804:824-146804:905',
)


process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/filtering.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
