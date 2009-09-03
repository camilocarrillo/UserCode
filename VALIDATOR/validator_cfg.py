import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/tmp/carrillo/kktau300GeVx1000WithRPC.root' ##for kktaus
##    'file:/tmp/carrillo/STAU_10TeV_247_2_2_3_x1000.root' ## for staus
##    'file:/tmp/carrillo/STAU_10TeV_247_2_2_10_x1000.root' ## for staus
    )
)

process.demo = cms.EDAnalyzer('VALIDATOR',
 partLabel = cms.untracked.string("genParticles"),
 muonRPCDigis = cms.untracked.string('muonRPCDigis'),
 partid = cms.untracked.int32(-2000015), ##for kktau
## partid = cms.untracked.int32(-1000015), ##for staus
 rootFileName = cms.untracked.string('validation.root')
)


process.p = cms.Path(process.demo)
