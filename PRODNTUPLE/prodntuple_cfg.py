import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#	'file:/tmp/carrillo/70195_W2_S4_St1_A.root'
#	'file:70195_W2_S4_St1.FEECAD77-49C6-DD11-812D-001D0967DB11.root'
#	'rfio:/castor/cern.ch/user/c/carrillo/skimByChamber/70195_W2_S4_St1_A.root'
	'rfio:/castor/cern.ch/user/c/carrillo/skimByChamber/70195_W2_S4_St1_B.root'
#	'rfio:/castor/cern.ch/user/c/carrillo/skimByChamber/70195_W2_S4_St1_C.root'
    )
)

process.demo = cms.EDAnalyzer('PRODNTUPLE'
)


process.p = cms.Path(process.demo)
