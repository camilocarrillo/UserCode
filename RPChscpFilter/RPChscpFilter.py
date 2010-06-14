import FWCore.ParameterSet.Config as cms

process = cms.Process("SelRPChscpEvents")

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
   rootFileName = cms.untracked.string('/tmp/carrillo/hscp.root'),
   MinRPCRecHits = cms.untracked.int32(2), #Hits in tracker track
   rootFileNameCal = cms.untracked.string('/afs/cern.ch/user/c/carrillo/scratch0/muonMonitor/PromptReco/PromptReco.root'),
   synchth = cms.untracked.double(0.02), #percentage of RPCRecHIts outside bx=0
   minIntegral = cms.untracked.double(20), #minimum number of hits asociated to a track in order to say something about the efficiency
   minMean = cms.untracked.double(0.02)
)

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('file:/tmp/carrillo/gluino_200GeV_GEN-SIM-RECO_central_1.root')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/filtergluino_200GeV_GEN-SIM-RECO_central_1.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
