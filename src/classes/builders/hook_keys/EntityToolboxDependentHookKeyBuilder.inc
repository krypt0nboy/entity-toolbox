<?php

/**
 * Class EntityToolboxDependentHookKeyBuilder
 */
class EntityToolboxDependentHookKeyBuilder extends EntityDependentHookKeyBuilder {
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

  /**
   *
   */
  protected function postSetEntityType() {
    $toolboxInfo = entity_toolbox_get_info($this->entityType);
    $this->__set('toolbox_info', $toolboxInfo);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $this->templateVars += $this->extractToolboxInfoTemplateVars();
    parent::initTemplateVars();
  }

  /**
   * @return array
   */
  public function extractToolboxInfoTemplateVars() {
    $extract = $this->extractTemplateVars($this->getToolboxInfo(), '', 'toolbox_info_');
    $extract += array('toolbox_info_entity_type' => $this->entityType);

    return $extract;
  }

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'toolbox_info' => $this->toolboxInfo,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}