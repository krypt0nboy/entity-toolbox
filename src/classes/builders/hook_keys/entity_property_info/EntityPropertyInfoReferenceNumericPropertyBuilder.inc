<?php

/**
 * Class EntityPropertyInfoReferenceNumericPropertyBuilder
 */
class EntityPropertyInfoReferenceNumericPropertyBuilder extends EntityPropertyInfoPropertyBuilder {
  use ReferenceDependentTraits, ReferenceDependentBuilderTraits;
  /**
   * @var EntityPropertyInfoReferencePropertyBuilder
   */
  protected $referencePropertyBuilder;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'property_type' => 'integer',
        'model_class'   => 'EntityPropertyInfoReferenceNumericPropertyModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractReferenceInfoTemplateVars();
    $vars += $this->getReferencePropertyBuilder()
                  ->extractToolboxInfoPropertyTemplateVars();

    return EntityDependentHookKeyBuilder::initTemplateVars($vars);
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

  /**
   * @return array
   */
  protected function buildClear() {
    return array($this->referencePropertyBuilder->getPropertyName());
  }
}