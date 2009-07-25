import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/tmp/carrillo/kktau300GeVx1000WithRPC.root'
    )
)

process.demo = cms.EDAnalyzer('TrackRPC',
  tracks = cms.untracked.string('standAloneMuons'),
  partLabel = cms.untracked.string("genParticles"),
  rootFileName = cms.untracked.string('/tmp/carrillo/hscp.root'),

)


process.p = cms.Path(process.demo)
