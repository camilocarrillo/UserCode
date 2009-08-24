import FWCore.ParameterSet.Config as cms

process = cms.Process("IGUANA") 
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff") 
process.load("Configuration.StandardSequences.Geometry_cff") 
process.load("Configuration.StandardSequences.MagneticField_cff") 
process.load("Configuration.StandardSequences.Reconstruction_cff") 
 
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/tmp/carrillo/STAU_10TeV_247_2_2_3_x1000.root')
)

from FWCore.MessageLogger.MessageLogger_cfi import * 
 
process.prefer("GlobalTag") 
process.GlobalTag.connect = "frontier://PromptProd/CMS_COND_21X_GLOBALTAG"
#process.GlobalTag.globaltag = "IDEAL_V9::All"
#process.GlobalTag.globaltag = "CRUZET4_V6P::All"
process.GlobalTag.globaltag = "COSMMC_21X::All"

process.load("VisFramework.VisFrameworkBase.VisConfigurationService_cff") 
process.VisConfigurationService.VisAutoStart = False
process.VisConfigurationService.VisCaloAnnotation = False 
process.VisConfigurationService.Views = ('RPhi Window', 'RZ Window') 
process.VisConfigurationService.EnabledTwigs = ('/Objects/CMS Event and Detector/Muon DT Event/DT 4DSegment', 
                                                '/Objects/CMS Event and Detector/Muon RPC Event/RPC RecHit', 
                                                '/Objects/CMS Event and Detector/Muon/Barrel/Drift Tubes', 
                                                '/Objects/CMS Event and Detector/Muon/Endcap/CSCs', 
                                                '/Objects/CMS Event and Detector/Magnet', 
                                                '/Objects/Event Collections/Run and Event Number' 
                                                ) 
process.VisConfigurationService.ContentProxies = ('Framework/EventSetup', 
                                                  'Reco/MuonDT', 
                                                  'Reco/MuonCSC', 
                                                  'Reco/MuonRPC', 
                                                  'Reco/Muon') 
