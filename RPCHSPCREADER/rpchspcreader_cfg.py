import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    
    firstEvent = cms.untracked.uint32(1),

    fileNames = cms.untracked.vstring(
#        'file:/afs/cern.ch/user/c/carrillo/scratch0/hscpPROD/jchen/testsingle.root'
#         'file:/tmp/carrillo/testsingle.root'
#         'file:/tmp/carrillo/testsingle10Rec.root'
#         'file:/tmp/carrillo/testsingle10Rec300GeV.root'
	  'file:/tmp/carrillo/rechit300GeV.root'
#         'file:/tmp/carrillo/GEN_SIM_RECO.root'
#          'file:/tmp/carrillo/STAU_10TeV_156_2_2_3_x1000.root'
#          'rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_2_2_3/STAU_10TeV_156_2_2_3_x1000.root'
    )
)

process.demo = cms.EDAnalyzer("RPCHSPCREADER",
    partLabel = cms.untracked.string("genParticles")
#   partLabel = cms.untracked.string("genParticleCandidates")
)


process.p = cms.Path(process.demo)
