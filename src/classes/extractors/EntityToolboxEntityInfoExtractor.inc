<?php

/**
 * Class EntityToolboxEntityInfoExtractor
 *
 * Extracts info from hook_entity_toolbox_entity_info().
 *
 * @see hook_entity_toolbox_entity_info().
 */
class EntityToolboxEntityInfoExtractor extends InfoExtractor {

  /** {@inheritdoc} */
  public function __construct($version, array $extractMethods = array()) {
	$methods = array(
	  'entity_type'      => 'extractEntityType',
	  'fieldable'        => 'extractFieldable',
	  'bundle_of'        => 'extractBundleOf',
	  'bundle_entity'    => 'extractBundleEntity',
	  'has_translations' => 'extractHasTranslations',
	  'has_revisions'    => 'extractHasRevisions',
	  'exportable'       => 'extractExportable',
	  'paths'            => 'extractPaths',
	  'module'           => 'extractModule',
	  'labels'           => 'extractLabels',
	  'label'            => 'extractLabel',
	  'label_plural'     => 'extractLabelPlural',
	  'classes'          => 'extractClasses',
	  'callbacks'        => 'extractCallbacks',
	  'base_table'       => 'extractBaseTable',
	  'revision_table'   => 'extractRevisionTable',
	  'tables'           => 'extractTables',
	  'keys'             => 'extractKeys',
	  'children_inherit' => 'extractChildrenInherit',
	  'operations'       => 'extractOperations',
	  'entity_group'     => 'extractEntityGroup',
	  'api'              => 'extractApi',
	);
	$merged  = array_merge($methods, $extractMethods);
	parent::__construct($version, 'entity_toolbox_entity_info', $merged);
  }

  protected function extractEntityType() {
	if (!empty($this->info['entity_type'])) {
	  return $this->info['entity_type'];
	}
  }

  protected function extractFieldable() {
	if (!empty($this->info['fieldable'])) {
	  return $this->info['fieldable'];
	}
  }

  protected function extractBundleOf() {
  }

  protected function extractBundleEntity() {
  }

  protected function extractHasTranslations() {
  }

  protected function extractHasRevisions() {
  }

  protected function extractExportable() {
  }

  protected function extractPaths() {
  }

  protected function extractModule() {
  }

  protected function extractLabels() {
  }

  protected function extractLabel() {
  }

  protected function extractLabelPlural() {
  }

  protected function extractClasses() {
  }

  protected function extractCallbacks() {
  }

  protected function extractBaseTable() {
  }

  protected function extractRevisionTable() {
  }

  protected function extractTables() {
  }

  protected function extractKeys() {
  }

  protected function extractChildrenInherit() {
  }

  protected function extractOperations() {
  }

  protected function extractEntityGroup() {
  }

  protected function extractApi() {
  }

}

/**
 * Class EntityToolboxEntityInfoExtractorBeta
 *
 * Extracts info from hook_entity_toolbox_entity_info() for the beta version.
 */
class EntityToolboxEntityInfoExtractorApi1 extends EntityToolboxEntityInfoExtractor {
  public function __construct() {
	parent::__construct("1");
  }
}