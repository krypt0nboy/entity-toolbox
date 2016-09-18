<?php

/**
 * Class EntityToolboxDependentHookKeyBuilder
 */
class EntityToolboxDependentHookKeyBuilder extends EntityDependentHookKeyBuilder {
  use EntityToolboxDependentTraits, EntityToolboxDependentBuilderTraits, EntityToolboxPropertiesDependentTraits;

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractToolboxInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /** {{@inheritdoc}} */
  protected function autoSet() {
    parent::autoSet();
    $this->autoSetProperties();
  }

  /** {{@inheritdoc}} */
  protected function generateHelpers() {
    parent::generateHelpers();
    $this->setPropsHelper($this->propsHelperGetInstance());
  }

  /**
   * @return \ToolboxPropertiesHelper
   */
  protected function propsHelperGetInstance() {
    return $this->helperGetInstance('ToolboxPropertiesHelper');
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'toolbox_info' => $this->toolboxInfo,
    ), $args);
    if (isset($this->groupName)) {
      $args = $this->mergeConstructArgs(array(
        'group_name' => $this->groupName,
        'group_info' => $this->groupInfo,
      ), $args);
    }

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}