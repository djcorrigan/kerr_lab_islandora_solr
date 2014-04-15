kerr_lab_islandora_solr
=======================

The Islandora Solr configuration for the Kerr Marine Products Lab.

This repository was forked from the repository https://github.com/Islandora/islandora_solr_search

The following functionalities were added to this Solr configuration:
Added fields for indexing Drupal content as well as Fedora content (using code from Discovery Garden) (in xml/schema.xml)
Custom search results for Drupal content (URLs and custom thumbnails) (in theme/theme.inc)
Indexing capabilities for Islandora Lab Objects:
  xml/islandora_transforms/EML_to_solr.xslt transforms EML XML to Solr XML (used for objects from the Specimen Solution Pack - https://github.com/ncphillips/islandora_lab_object_specimen)
  
  xml/islandora_transforms/fraction_to_solr.xslt transforms the Fraction datastream to Solr XML (used for objects from the Fraction Solution Pack - https://github.com/ncphillips/islandora_lab_object_fraction)
  xml/islandora_transforms/person_mads_to_solr.xslt transforms the MADS datastream to Solr XML (used for objects from the Base Solution Pack with the Person content model - https://github.com/ncphillips/islandora_bioinformatics_base)
  xml/islandora_transforms/project_mads_to_solr.xslt transforms the MADS datastream to Solr XML (used for objects from the Base Solution Pack with the Project content model - https://github.com/ncphillips/islandora_bioinformatics_base)
  xml/islandora_transforms/foxmlToSolr.xslt completes the transformation process
    foxmlToSolr.xslt must be placed in <gsearch-home>/WEB-INF/classes/fgsconfigFinal/index/FgsIndex
Installed the Islandora Geo Display Profile for searching coordinates (islandora_solr_geo)
Added custom markers for map results (in islandora_solr_geo/includes/theme.inc)
Added functionality for trimming the full-text field in search results (in includes/results.inc)
