import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       'file:/tmp/carrillo/KKtaugen.root'
#	'file:/afs/cern.ch/user/c/carrillo/scratch0/hscpPROD/321/stau/stau156/stau156gen.root'
# 'rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_1_1/ROOT/GEN_STAU156_3_3_1_x1000.root'
    )
)

process.demo = cms.EDAnalyzer('HEPMCPRODUCTSANALYZER',
	 HepMCProduct             = cms.InputTag("generator"),
	 GenLeadTrackPt           = cms.double(0),
	 GenEta                   = cms.double(5)
)


process.p = cms.Path(process.demo)
