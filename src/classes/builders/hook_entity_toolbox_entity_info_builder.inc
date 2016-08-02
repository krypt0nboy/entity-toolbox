<?php

/**
 * Class hook_entity_toolbox_entity_info_builder
 *
 * Builds an entity default hook_entity_toolbox_entity_info() data.
 *
 * @see hook_entity_toolbox_entity_info().
 */
class hook_entity_toolbox_entity_info_builder {

  /**
   * @var string $entityType
   *   The entity type for which to build the info.
   */
  protected $entityType;
  /**
   * @var array $rawInfo
   *   An array containing the raw data retrieved by entity toolbox.
   */
  protected $rawInfo;
  /**
   * @var array $processedInfo
   *   An array containing the processed data.
   */
  protected $processedInfo;
  /**
   * @var bool $fieldable
   *   A boolean indicating if the entity type is fieldable or not.
   */
  protected $fieldable;
  /**
   * @var bool $defaultHasRevisions
   */
  protected $defaultHasRevisions;
  /**
   * @var bool $defaultHasTranslations
   */
  protected $defaultHasTranslations;
  /**
   * @var bool $defaultExportable
   */
  protected $defaultExportable;
  /**
   * @var array $defaultProperties
   */
  protected $defaultProperties;

  /**
   * hook_entity_toolbox_entity_info_builder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param array       $rawInfo
   *   The entity raw info retrieved by hook_entity_toolbox_entity_info().
   * @param null|bool   $fieldable
   *   If the entity type is fieldable or not.
   * @param array       $defaultProperties
   *   An array containing the default properties types to add if missing.
   *   (Eg : "id", "bundle")
   *
   * @throws \Exception
   */
  public function __construct($entityType = NULL, $rawInfo = array(), $fieldable = NULL, $defaultProperties = array()) {
	if (empty($entityType)) {
	  throw new MissingEntityTypeException(array('class' => self::class));
	}
	$this->entityType = $entityType;
	if (!empty($rawInfo)) {
	  $this->rawInfo = $rawInfo;
	}
	if (!empty($fieldable)) {
	  $this->fieldable = $fieldable;
	}
	$this->defaultProperties = $defaultProperties;
  }

  /**
   * Processes the raw info retrieved by entity toolbox.
   *
   * @param array $rawInfo
   *
   * @throws \Exception
   */
  protected function processRawInfo($rawInfo = array()) {
	if (empty($this->rawInfo) && empty($rawInfo)) {
	  throw new MissingRawToolboxInfoException();
	}
	$this->processEntityType();
	$this->processFieldable();
	$this->processPaths();
	$this->processModule();
	$this->processHasRevisions();
	$this->processHasTranslations();
	$this->processExportable();
	$this->processLabels();
	$this->processClasses();
	$this->processProperties();
	$this->processSchemas();
	$this->processKeys();
  }

  /**
   * Return the entity toolbox processed info.
   *
   * @return array
   *
   * @throws \Exception
   */
  public function build() {
	$this->processRawInfo();

	return $this->processedInfo;
  }

  protected function processEntityType() {
	$info                = &$this->processedInfo;
	$info['entity_type'] = !empty($this->rawInfo['entity_type']) ? $this->rawInfo['entity_type'] : $this->entityType;
  }

  protected function processFieldable() {
	$info              = &$this->processedInfo;
	$info['fieldable'] = $this->fieldable;
  }

  protected function processPaths() {
	$info           = &$this->processedInfo;
	$info['module'] = !empty($this->rawInfo['module']) ? $this->rawInfo['module'] : array();
  }

  protected function processModule() {
	$info           = &$this->processedInfo;
	$info['module'] = !empty($this->rawInfo['module']) ? $this->rawInfo['module'] : "";
  }

  /**
   * Processes the provided "has_revisions" data.
   */
  protected function processHasRevisions() {
	$info                  = &$this->processedInfo;
	$info['has_revisions'] = !empty($this->rawInfo['has_revisions']) ? $this->rawInfo['has_revisions'] : $this->defaultHasRevisions;
  }

  /**
   * Processes the provided "has_translations" data.
   */
  protected function processHasTranslations() {
	$info                     = &$this->processedInfo;
	$info['has_translations'] = !empty($this->rawInfo['has_translations']) ? $this->rawInfo['has_translations'] : $this->defaultHasTranslations;
  }

  /**
   * Processes the provided "exportable" data.
   */
  protected function processExportable() {
	$info                     = &$this->processedInfo;
	$info['has_translations'] = !empty($this->rawInfo['exportable']) ? $this->rawInfo['exportable'] : $this->defaultExportable;
  }

  /**
   * Processes the provided "labels" data.
   */
  protected function processLabels() {
	$info           = &$this->processedInfo;
	$raw            = $this->raw('labels');
	$default        = toolbox_entity_default_labels_info_build($this->entityType);
	$info['labels'] = array_merge($default, !empty($raw) ? $raw : array());
  }

  /**
   * Processes the provided "classes" data.
   */
  protected function processClasses() {
	$info            = &$this->processedInfo;
	$raw             = $this->raw('classes');
	$default         = toolbox_entity_default_classes_info_build($this->entityType, $this->fieldable);
	$info['classes'] = array_merge($default, !empty($raw) ? $raw : array());
  }

  /**
   * Processes the provided "schemas" data.
   */
  protected function processSchemas() {
	$info            = &$this->processedInfo;
	$raw             = $this->raw('schemas');
	$info['schemas'] = array();
  }

  /**
   * Processes the provided "properties" data.
   */
  protected function processProperties() {
	$info          = &$this->processedInfo;
	$set_types     = array_unique(array_column($this->rawInfo['properties'], 'type'));
	$missing_types = array_diff($this->defaultProperties, $set_types);
	foreach ($missing_types as $missing_type) {
	  //@todo add property
	}
	foreach ($this->rawInfo['properties'] as $property) {

	}
  }

  /**
   * Process a property from "rawInfo".
   *
   * @param array $propertyInfo
   *   The property info.
   */
  protected function processProperty(&$propertyInfo) {

  }

  /**
   * Processes the provided "keys" data.
   */
  protected function processKeys() {
	$info         = &$this->processedInfo;
	$raw          = $this->raw('keys');
	$info['keys'] = array();
  }

  /**
   * Processes the provided "children_inherit" data.
   */
  protected function processChildrenInherit() {
	$info                     = &$this->processedInfo;
	$raw                      = $this->raw('children_inherit');
	$info['children_inherit'] = array();
  }

  protected function raw($key) {
	return !empty($this->rawInfo[$key]) ? $this->rawInfo[$key] : NULL;
  }

}

/**
 * Class hook_entity_toolbox_fieldable_entity_info_builder
 *
 * Builds default hook_entity_toolbox_entity_info() data for fieldable entity types.
 *
 * @see hook_entity_toolbox_entity_info().
 */
class hook_entity_toolbox_fieldable_entity_info_builder extends hook_entity_toolbox_entity_info_builder {
  /**
   * @var string $defaultBundleEntity
   *   The default bundle entity.
   */
  protected $defaultBundleEntity;

  /** {@inheritdoc} */
  public function __construct($entityType, $rawInfo = array()) {
	$defaultProperties = array(
	  'id',
	  'bundle',
	);
	parent::__construct($entityType, $rawInfo, TRUE, $defaultProperties);
	//@todo manage settings
	$this->defaultHasRevisions    = TRUE;
	$this->defaultHasTranslations = TRUE;
	$this->defaultExportable      = FALSE;
  }

  /**
   * {@inheritdoc}
   */
  protected function processRawInfo($rawInfo = array()) {
	parent::processRawInfo($rawInfo);
	$this->processBundleEntity();
  }

  protected function processBundleEntity() {
	$info                  = &$this->processedInfo;
	$raw                   = $this->raw('bundle_entity');
	$info['bundle_entity'] = !empty($raw) ? $raw : string_template_process('%entity_type%_type', array('entity_type' => $this->entityType));
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
	parent::build();

	return $this->processedInfo;
  }
}

/**
 * Class hook_entity_toolbox_not_fieldable_entity_info_builder
 *
 * Builds default hook_entity_toolbox_entity_info() data for non fieldable entity types.
 *
 * @see hook_entity_toolbox_entity_info().
 */
class hook_entity_toolbox_not_fieldable_entity_info_builder extends hook_entity_toolbox_entity_info_builder {
  /**
   * @var string $defaultBundleOf
   *   The default entity bundle.
   */
  protected $defaultBundleOf;

  /** {@inheritdoc} */
  public function __construct($entityType, $rawInfo = array()) {
	$defaultProperties = array(
	  'id',
	  'bundle',
	);
	parent::__construct($entityType, $rawInfo, FALSE, $defaultProperties);
	//@todo manage settings
	$this->defaultHasRevisions    = FALSE;
	$this->defaultHasTranslations = FALSE;
	$this->defaultExportable      = TRUE;
  }

  /**
   * Processes the provided "bundle_of" data.
   */
  protected function processBundleOf() {
	$info              = &$this->processedInfo;
	$raw               = $this->raw('bundle_of');
	$info['bundle_of'] = !empty($raw) ? $raw : preg_replace('/_type/', '', $this->entityType);
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
	parent::build();

	return $this->processedInfo;
  }
}