import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#       'file:/tmp/carrillo/kktau300GeVx1000WithRPC.root'
#        'file:/tmp/carrillo/STAU_10TeV_156_2_2_3_x1000.root'
        'file:/tmp/carrillo/STAU_10TeV_247_2_2_10_x1000.root'
#        'file:/tmp/carrillo/KKtau300_223_10TeV_2kevt.root'

    )
)

process.demo = cms.EDAnalyzer('TrackRPC',
  tracks = cms.untracked.string('standAloneMuons'),
  partLabel = cms.untracked.string("genParticles"),
  rootFileName = cms.untracked.string('/tmp/carrillo/hscpstaus247.root'),
  ##kktaus
  #partid = cms.untracked.int32(-2000015) 

  ##staus
  partid = cms.untracked.int32(-1000015) 
  
)

process.p = cms.Path(process.demo)
