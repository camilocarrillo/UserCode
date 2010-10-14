import FWCore.ParameterSet.Config as cms

process = cms.Process("PRINTOUT")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.MuonGeometryDBConverter = cms.EDAnalyzer("MuonGeometryDBConverter",
                                                 input = cms.string("ideal"),
                                                 output = cms.string("xml"),
                                                 outputXML = cms.PSet(fileName = cms.string("output.xml"),
                                                                      relativeto = cms.string("none"),
                                                                      survey = cms.bool(False),
                                                                      rawIds = cms.bool(True),
                                                                      eulerAngles = cms.bool(False),
                                                                      precision = cms.int32(8),
                                                                      suppressDTBarrel = cms.untracked.bool(True),
                                                                      suppressDTWheels = cms.untracked.bool(True),
                                                                      suppressDTStations = cms.untracked.bool(True),
                                                                      suppressDTChambers = cms.untracked.bool(False),
                                                                      suppressDTSuperLayers = cms.untracked.bool(True),
                                                                      suppressDTLayers = cms.untracked.bool(True),
                                                                      suppressCSCEndcaps = cms.untracked.bool(True),
                                                                      suppressCSCStations = cms.untracked.bool(True),
                                                                      suppressCSCRings = cms.untracked.bool(True),
                                                                      suppressCSCChambers = cms.untracked.bool(True),
                                                                      suppressCSCLayers = cms.untracked.bool(True)
                                                                      ))

process.Path = cms.Path(process.MuonGeometryDBConverter)
