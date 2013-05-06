import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_upscope_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#       'file:/afs/cern.ch/user/c/carrillo/workspace/GRPC/CMSSW_6_1_2/src/SingleMuPt40_RE4_cfi_GEN_SIM_upscope.root'
	'file:/afs/cern.ch/user/c/carrillo/workspace/GRPC/CMSSW_6_1_2/src/SingleMuPt40_RE4_cfi_GEN_SIM_upscope_x10000.root'
    )
)

process.demo = cms.EDAnalyzer('SIMHITANALIZER'
)


process.p = cms.Path(process.demo)
