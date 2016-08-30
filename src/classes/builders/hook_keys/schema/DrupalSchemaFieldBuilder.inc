<?php

/**
 * Class DrupalSchemaFieldBuilder
 */
class DrupalSchemaFieldBuilder extends SchemaKeyBuilder {
  /**
   * @var string $fieldName
   */
  protected $fieldName;

  /**
   * @var string $propertyName
   */
  protected $propertyName;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'DrupalSchemaFieldModel'
    ), $args);
    parent::__construct($args);
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
  public function getFieldName() {
    return $this->fieldName;
  }

  /**
   * @param string $fieldName
   */
  public function setFieldName($fieldName) {
    $this->fieldName = $fieldName;
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
}