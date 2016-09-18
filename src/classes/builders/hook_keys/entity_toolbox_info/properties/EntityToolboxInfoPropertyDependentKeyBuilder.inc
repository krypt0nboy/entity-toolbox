<?php

class EntityToolboxInfoPropertyDependentKeyBuilder extends EntityToolboxInfoKeyBuilder {
  use PropertyDependentTraits;

  /**
   * @var array $rawPropertyInfo
   */
  protected $rawPropertyInfo = array();

  /**
   * @return array
   */
  public function getRawPropertyInfo() {
    return $this->rawPropertyInfo;
  }

  /**
   * @param array $rawPropertyInfo
   */
  public function setRawPropertyInfo($rawPropertyInfo) {
    $this->rawPropertyInfo = $rawPropertyInfo;
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->getPropertyInstance()->extractSelfVars();
    parent::initTemplateVars($vars);
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_name'     => $this->propertyName,
      'property_type'     => $this->propertyType,
      'property_instance' => $this->propertyInstance,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}