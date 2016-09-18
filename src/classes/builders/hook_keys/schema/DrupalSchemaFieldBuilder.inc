<?php

/**
 * Class DrupalSchemaFieldBuilder
 */
class DrupalSchemaFieldBuilder extends SchemaKeyBuilder {
  use PropertyDependentTraits, PropertyDependentBuilderTraits;
  /**
   * @var string $fieldName
   */
  protected $fieldName;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'DrupalSchemaFieldModel'
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractToolboxInfoPropertyTemplateVars();
    parent::initTemplateVars($vars);
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

  protected function validateDefault($build) {
    if ($this->propertyType == 'entity_id') {
      $this->structure['default']['unset if'] = 0;

      return 0;
    }
    else {
      if ($this->propertyType == 'entity_revision_id') {
        $this->structure['default']['unset if'] = 0;

        return 0;
      }
      else {
        return $build;
      }
    }
  }

  protected function validateSerialize($build) {
    if ($this->isValueTemplate($build) || ($build == FALSE)) {
      return 0;
    }
    else {
      return $build;
    }
  }

  protected function validateSize($build) {
    if ($this->isValueTemplate($build) || ($build == 0)) {
      return 0;
    }
    else {
      return $build;
    }
  }

  protected function validateScale($build) {
    if ($this->isValueTemplate($build) || ($build == 0)) {
      return 0;
    }
    else {
      return $build;
    }
  }

  protected function validatePrecision($build) {
    if ($this->isValueTemplate($build) || ($build == 0)) {
      return 0;
    }
    else {
      return $build;
    }
  }

  protected function validateBinary($build) {
    if ($this->isValueTemplate($build) || ($build == 0)) {
      return FALSE;
    }
    else {
      return $build;
    }
  }

}