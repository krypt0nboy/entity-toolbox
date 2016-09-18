<?php

/**
 * Class EntityToolboxDependentTraits
 */
trait EntityToolboxDependentTraits {
  /**
   * @var array $toolboxInfo
   */
  protected $toolboxInfo = array();

  /**
   * @return array
   */
  public function getToolboxInfo() {
    return $this->toolboxInfo;
  }

  /**
   * @param array $toolboxInfo
   */
  public function setToolboxInfo($toolboxInfo) {
    $this->toolboxInfo = $toolboxInfo;
  }

  public function autoSetToolboxInfo() {
    $this->__set('toolbox_info', entity_toolbox_get_info($this->entityType));
  }
}