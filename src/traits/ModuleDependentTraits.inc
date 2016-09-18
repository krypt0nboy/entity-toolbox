<?php

/**
 * Class ModuleDependentTraits
 */
trait ModuleDependentTraits {
  /**
   * @var string $module
   */
  protected $module;
  /**
   * @var array $moduleInfo
   */
  protected $moduleInfo = array();
  /**
   * @var array $moduleEntities
   */
  protected $moduleEntities = array();

  /**
   * @return string
   */
  public function getModule() {
    return $this->module;
  }

  /**
   * @param string $module
   */
  public function setModule($module) {
    $this->module = $module;
  }

  /**
   * @return array
   */
  public function getModuleInfo() {
    return $this->moduleInfo;
  }

  /**
   * @param array $moduleInfo
   */
  public function setModuleInfo($moduleInfo) {
    $this->moduleInfo = $moduleInfo;
  }

  /**
   * @return array
   */
  public function getModuleEntities() {
    return $this->moduleEntities;
  }

  /**
   * @param array $moduleEntities
   */
  public function setModuleEntities($moduleEntities) {
    $this->moduleEntities = $moduleEntities;
  }

  /**
   * Auto set module.
   */
  public function autoSetModule() {
    $module = entity_get_module_info($this->entityType);
    $this->__set('module', $module);
  }

  /**
   * Auto set moduleInfo.
   */
  public function autoSetModuleInfo() {
    $this->__set('module_info', entity_toolbox_module_info_get_info($this->module));
  }

  /**
   * Auto set moduleEntities.
   */
  public function autoSetModuleEntities() {
    $this->__set('module_entities', $this->moduleInfo->entities);
  }
}