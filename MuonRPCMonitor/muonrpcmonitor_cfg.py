import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Core.DQM_cfg")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/tmp/carrillo/gluino_200GeV_GEN-SIM-RECO_central_1.root')
)

process.demo = cms.EDAnalyzer('MuonRPCMonitor',
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rootFileName = cms.untracked.string('/tmp/carrillo/hscp.root'),
   MinRPCRecHits = cms.untracked.int32(2)
)


process.p = cms.Path(process.demo)
