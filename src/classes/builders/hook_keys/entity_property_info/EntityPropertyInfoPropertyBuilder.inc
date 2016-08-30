<?php

/**
 * Class EntityPropertyInfoPropertyBuilder
 */
class EntityPropertyInfoPropertyBuilder extends EntityPropertyInfoKeyBuilder {
  /**
   * @var string $propertyType
   *   The toolbox property type.
   */
  protected $propertyType;
  /**
   * @var array $propertyTypeInfo
   *   The toolbox property type info.
   */
  protected $propertyTypeInfo = array();
  /**
   * @var string $propertyName
   *   The property name.
   */
  protected $propertyName;
  /**
   * @var array $entityPropertyInfo
   *   The property info within the toolbox array.
   */
  protected $entityPropertyInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityPropertyInfoPropertyModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function getParentBuilder() {
    /** @var EntityPropertyInfoPropertiesBuilder $parentBuilder */
    $parentBuilder = parent::getParentBuilder();

    return $parentBuilder;
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $flattened = $this->extractTemplateVars($this->toolboxInfo['properties'][$this->propertyName], '', 'property_');
    $this->templateVars += $flattened;
    parent::initTemplateVars();
  }

  /**
   * @return string
   */
  public function getPropertyType() {
    return $this->propertyType;
  }

  /**
   * @param string $propertyType
   */
  public function setPropertyType($propertyType) {
    $this->propertyType = $propertyType;
  }

  /**
   * @return string
   */
  public function getPropertyName() {
    return $this->propertyName;
  }

  /**
   * @param string $propertyName
   */
  public function setPropertyName($propertyName) {
    $this->propertyName = $propertyName;
  }

  protected function postSetToolboxInfo() {
    $this->__set('entity_property_info', $this->toolboxInfo['properties'][$this->constructArgs['property_name']]);
  }

  /**
   * @return array
   */
  public function getEntityPropertyInfo() {
    return $this->entityPropertyInfo;
  }

  /**
   * @param array $entityPropertyInfo
   */
  public function setEntityPropertyInfo($entityPropertyInfo) {
    $this->entityPropertyInfo = $entityPropertyInfo;
  }

  /**
   * Builds the "type".
   */
  protected function buildType() {
  }

  /**
   * Builds the "bundle".
   */
  protected function buildBundle() {
  }

  /**
   * Builds the "options list".
   */
  protected function buildOptionsList() {
  }

  /**
   * Builds the "getter callback".
   */
  protected function buildGetterCallback() {
  }

  /**
   * Builds the "setter callback".
   */
  protected function buildSetterCallback() {
  }

  /**
   * Builds the "validation callback".
   */
  protected function buildValidationCallback() {
  }

  /**
   * Builds the "access callback".
   */
  protected function buildAccessCallback() {
  }

  /**
   * Builds the "setter permission".
   */
  protected function buildSetterPermission() {
  }

  /**
   * Builds the "schema field".
   */
  protected function buildSchemaField() {
  }

  /**
   * Builds the "queryable".
   */
  protected function buildQueryable() {
  }

  /**
   * Builds the "query callback".
   */
  protected function buildQueryCallback() {
  }

  /**
   * Builds the "required".
   */
  protected function buildRequired() {
  }

  /**
   * Builds the "field".
   */
  protected function buildField() {
  }

  /**
   * Builds the "computed".
   */
  protected function buildComputed() {
  }

  /**
   * Builds the "entity views field".
   */
  protected function buildEntityViewsField() {
  }

  /**
   * Builds the "sanitized".
   */
  protected function buildSanitized() {
  }

  /**
   * Builds the "sanitize".
   */
  protected function buildSanitize() {
  }

  /**
   * Builds the "raw getter callback".
   */
  protected function buildRawGetterCallback() {
  }

  /**
   * Builds the "clear".
   */
  protected function buildClear() {
  }

  /**
   * Builds the "property info".
   */
  protected function buildPropertyInfo() {
  }

  /**
   * Builds the "property info alter".
   */
  protected function buildPropertyInfoAlter() {
  }

  /**
   * Builds the "property defaults".
   */
  protected function buildPropertyDefaults() {
  }

  /**
   * Builds the "autocreation".
   */
  protected function buildAutoCreation() {
  }

  /**
   * Builds the "translatable".
   */
  protected function buildTranslatable() {
  }

  /**
   * Builds the "entity token".
   */
  protected function buildToken() {
  }
}