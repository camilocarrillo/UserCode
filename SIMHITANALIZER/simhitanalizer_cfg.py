import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#      'file:/afs/cern.ch/user/c/carrillo/scratch0/hscpPROD/jchen/testsingle.root'
#       'file:/tmp/carrillo/testsingle.root'
#       'file:/tmp/carrillo/GEN_SIM_RECO.root'
#	'file:/tmp/carrillo/testsingle.root'
#	'file:/tmp/carrillo/testsingle10Rec.root'
	'file:/tmp/carrillo/testsingle10Rec300GeV.root'
    )
)

process.demo = cms.EDAnalyzer('SIMHITANALIZER'
)


process.p = cms.Path(process.demo)
