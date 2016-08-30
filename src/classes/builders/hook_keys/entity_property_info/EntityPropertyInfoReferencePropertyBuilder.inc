<?php

/**
 * Class EntityPropertyInfoReferencePropertyBuilder
 */
class EntityPropertyInfoReferencePropertyBuilder extends EntityPropertyInfoPropertyBuilder {
  protected $reference;
  protected $referenceInfo = array();
  protected $numericPropertyBuilder;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
    $this->addNumericProperty();
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $flattened = array();
    $flattened += $this->extractTemplateVars($this->toolboxInfo['properties'][$this->propertyName], '', 'property_');
    $flattened += $this->extractTemplateVars($this
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
   *
   */
  protected function postSetEntityPropertyInfo() {
    $this->__set('reference', $this->entityPropertyInfo['reference']);
  }

  /**
   *
   */
  protected function postSetReference() {
    $this->__set('reference_info', entity_get_info($this->reference));
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
   *
   */
  protected function addNumericProperty() {
    $args                   = array(
      'property_name'              => $this->entityPropertyInfo['key'],
      'property_type'              => 'integer',
      'key_builder_class'          => 'EntityPropertyInfoReferenceNumericPropertyBuilder',
      'reference'                  => $this->reference,
      'reference_info'             => $this->referenceInfo,
      'reference_property_builder' => $this,
    );
    $numericPropertyBuilder = $this->getParentBuilder()->addProperty($args);
    $this->__set('numeric_property_builder', $numericPropertyBuilder);
  }
}