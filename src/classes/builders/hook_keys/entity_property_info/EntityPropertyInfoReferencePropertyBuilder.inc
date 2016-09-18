<?php

/**
 * Class EntityPropertyInfoReferencePropertyBuilder
 */
class EntityPropertyInfoReferencePropertyBuilder extends EntityPropertyInfoPropertyBuilder {
  use ReferenceDependentTraits, ReferenceDependentBuilderTraits;

  /**
   * @var EntityPropertyInfoReferenceNumericPropertyBuilder $numericPropertyBuilder
   */
  protected $numericPropertyBuilder;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractReferenceInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /**
   * @return mixed
   */
  public function getNumericPropertyBuilder() {
    return $this->numericPropertyBuilder;
  }

  /**
   * @param EntityPropertyInfoReferenceNumericPropertyBuilder $numericPropertyBuilder
   */
  public function setNumericPropertyBuilder($numericPropertyBuilder) {
    $this->numericPropertyBuilder = $numericPropertyBuilder;
  }

  /**
   * @return mixed
   */
  public function genNumericPropertyName() {
    return $this->propertyInfo['self_numeric_property'];
  }

  public function genNumericPropertyBuilderArgs() {
    $args = array(
      'property_name'              => $this->genNumericPropertyName(),
      'property_type'              => 'reference_numeric_property',
      'key_builder_class'          => 'EntityPropertyInfoReferenceNumericPropertyBuilder',
      'reference'                  => $this->reference,
      'reference_info'             => $this->referenceInfo,
      'reference_property_builder' => $this,
    );
  }

  /**
   * @return array
   */
  protected function buildClear() {
    return array($this->numericPropertyBuilder->getPropertyName());
  }
}