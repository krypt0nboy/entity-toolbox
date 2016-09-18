<?php

/**
 * Class EntityToolboxPropertiesDependentTraits
 */
trait EntityToolboxPropertiesDependentTraits {
  /**
   * @var array $properties
   *   The properties within toolbox info.
   */
  protected $properties = array();
  /**
   * @var ToolboxPropertiesHelper $propsHelper
   */
  protected $propsHelper;

  /**
   * @return array
   */
  public function getProperties() {
    return $this->properties;
  }

  /**
   * @param array $properties
   */
  public function setProperties($properties) {
    $this->properties = $properties;
  }

  /**
   * @return ToolboxPropertiesHelper
   */
  public function getPropsHelper() {
    return $this->propsHelper;
  }

  /**
   * @param ToolboxPropertiesHelper $propsHelper
   */
  public function setPropsHelper($propsHelper) {
    $this->propsHelper = $propsHelper;
  }

  public function autoSetProperties() {
    $this->__set('properties', $this->toolboxInfo['properties']);
  }
}