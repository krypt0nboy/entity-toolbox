<?php

/**
 * Class EntityToolboxDependentHookBuilder
 *
 * Used to build data when toolbox_info is required.
 */
class EntityToolboxDependentHookBuilder extends EntityDependentHookBuilder {
  /**
   * @var array $toolboxInfo
   */
  protected $toolboxInfo = array();

  protected function postSetEntityType() {
    $this->__set('toolbox_info', entity_toolbox_get_info($this->entityType));
  }

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

  /**
   * @return array
   */
  public function extractToolboxInfoTemplateVars() {
    return $this->extractTemplateVars($this->getToolboxInfo(), '', 'toolbox_info_');
  }
}