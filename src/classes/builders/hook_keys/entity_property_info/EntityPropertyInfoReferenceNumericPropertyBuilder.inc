<?php

/**
 * Class EntityPropertyInfoReferenceNumericPropertyBuilder
 */
class EntityPropertyInfoReferenceNumericPropertyBuilder extends EntityPropertyInfoPropertyBuilder {
  /**
   * @var string $reference
   */
  protected $reference;
  /**
   * @var array $referenceInfo
   */
  protected $referenceInfo = array();
  /**
   * @var EntityPropertyInfoReferencePropertyBuilder
   */
  protected $referencePropertyBuilder;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityPropertyInfoReferenceNumericPropertyModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $flattened = $this->extractTemplateVars($this->getReferencePropertyBuilder()
                                                 ->getEntityPropertyInfo(), '', 'reference_property_info_');
    $this->templateVars += $flattened;
    $vars = $this->getUpdatedTemplateVars();
    $this->setTemplateVars($vars);
  }

  /**
   * @return mixed
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * @param mixed $reference
   */
  public function setReference($reference) {
    $this->reference = $reference;
  }

  /**
   * @return array
   */
  public function getReferenceInfo() {
    return $this->referenceInfo;
  }

  /**
   * @param array $referenceInfo
   */
  public function setReferenceInfo($referenceInfo) {
    $this->referenceInfo = $referenceInfo;
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

  protected function postSetToolboxInfo() {
    $this->__set('reference', $this->constructArgs['reference']);
    $this->__set('entity_property_info', $this->toolboxInfo['properties'][$this->constructArgs['reference_property_builder']->getPropertyName()]);
  }

  /**
   *
   */
  protected function postSetReference() {
    $this->__set('reference_info', entity_get_info($this->reference));
  }
}