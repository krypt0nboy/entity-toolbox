<?php

/**
 * Class RelationDrupalSchemaBuilder
 */
class RelationDrupalSchemaBuilder extends DrupalSchemaBuilder {
  /**
   * @var string $propertyName
   */
  protected $propertyName;
  /**
   * @var string $reference
   */
  protected $reference;
  /**
   * @var array $referenceInfo
   */
  protected $referenceInfo = array();

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $flattened = array();
    $flattened += $this->extractTemplateVars($this->toolboxInfo['properties'][$this->propertyName], '', 'property_');
    $flattened += $this->extractTemplateVars($this->referenceInfo, '', 'reference_info_');
    $flattened += array('reference_info_entity_type' => $this->reference);
    $this->templateVars += $flattened;
    $vars = $this->getUpdatedTemplateVars();
    $this->setTemplateVars($vars);
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

  /**
   * @return string
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * @param string $reference
   */
  public function setReference($reference) {
    $this->reference = $reference;
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

  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('A relation table between %toolbox_info_entity_type% and %reference_info_%.');
  }
}