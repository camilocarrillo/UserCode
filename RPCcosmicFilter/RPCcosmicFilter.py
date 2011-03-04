import FWCore.ParameterSet.Config as cms

process = cms.Process("ReSelRPCcosmicEvents")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet(
##input = cms.untracked.int32(-1)
input = cms.untracked.int32(4500)
)

process.selRPC = cms.EDFilter("RPCcosmicFilter",
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rpcRecHits = cms.InputTag("rpcRecHits"),
   MinRPCRecHits = cms.untracked.int32(2), #Hits in tracker track
   rootFileName = cms.untracked.string('Piotr.root'),
   synchth = cms.untracked.double(0.02), #percentage of RPCRecHIts outside bx=0
   minIntegral = cms.untracked.double(20), #minimum number of hits asociated to a track in order to say something about the efficiency
   minMean = cms.untracked.double(0.02)
)

import FWCore.Utilities.FileUtils as FileUtils
##mylist = FileUtils.loadListFromFile('Zmumu')
mylist = FileUtils.loadListFromFile('list_antipv')
process.source = cms.Source("PoolSource",fileNames =
cms.untracked.vstring( *mylist ))

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring("selrpc")
    ),
    fileName = cms.untracked.string('/tmp/carrillo/filtering.root')
)

process.selrpc = cms.Path(process.selRPC)
process.outpath = cms.EndPath(process.FEVT)
