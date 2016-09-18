<?php

/**
 * Class EntityToolboxInfoReferenceNumericPropertyBuilder
 */
class EntityToolboxInfoReferenceNumericPropertyBuilder extends EntityToolboxInfoPropertyBuilder {
  use ReferenceDependentTraits, ReferenceDependentBuilderTraits;

  /**
   * @var EntityToolboxInfoReferencePropertyBuilder $referencePropertyBuilder
   */
  protected $referencePropertyBuilder;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_type' => 'entity_numeric_property',
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function constructSet($args) {
    parent::constructSet($args);
    $this->setReferencePropertyBuilder($this->parentBuilder);
  }

  /**
   * @return EntityPropertyInfoReferencePropertyBuilder
   */
  public function getReferencePropertyBuilder() {
    return $this->referencePropertyBuilder;
  }

  /**
   * @param mixed $referencePropertyBuilder
   */
  public function setReferencePropertyBuilder($referencePropertyBuilder) {
    $this->referencePropertyBuilder = $referencePropertyBuilder;
  }
}