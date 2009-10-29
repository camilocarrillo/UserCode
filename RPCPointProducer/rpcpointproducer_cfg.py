import FWCore.ParameterSet.Config as cms

##process = cms.Process("RPCPointProducer")
process = cms.Process("OWNPARTICLES")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V1::All'

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '//store/data/CRAFT09/Cosmics/RECO/v1/000/111/125/8A62785E-158D-DE11-884B-0030486730C6.root'
    )
)

process.rpcPointProducer = cms.EDProducer('RPCPointProducer',
  incldt = cms.untracked.bool(True),
  incldtMB4 = cms.untracked.bool(True),
  inclcsc = cms.untracked.bool(True),

  debug = cms.untracked.bool(True),

  rangestrips = cms.untracked.double(4.),
  rangestripsRB4 = cms.untracked.double(4.),
  MinCosAng = cms.untracked.double(0.85),
  MaxD = cms.untracked.double(80.0),
  MaxDrb4 = cms.untracked.double(150.0),

  cscSegments = cms.untracked.string('cscSegments'),
  dt4DSegments = cms.untracked.string('dt4DSegments')
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring('drop *',
        'keep *_dt4DSegments_*_*',
        'keep *_cscSegments_*_*',
        'keep *_rpcPointProducer_*_*',
        'keep *_rpcRecHits_*_*'),
  fileName = cms.untracked.string('/tmp/carrillo/output.root')
)
process.Timing = cms.Service("Timing")
  
process.p = cms.Path(process.rpcPointProducer)

process.e = cms.EndPath(process.out)
