<?php

require_once ENTITY_TOOLBOX_PATH . '/src/classes/helpers/entity_toolbox/ToolboxPropertiesHelper.inc';

/**
 * Class EntityToolboxDependentHookBuilder
 *
 * Used to build data when toolbox_info is required.
 */
class EntityToolboxDependentHookBuilder extends EntityDependentHookBuilder {
  use EntityToolboxDependentBuilderTraits, EntityToolboxDependentTraits, EntityToolboxPropertiesDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function autoSet() {
    parent::autoSet();
    if (!$this->__isset('toolbox_info')) {
      $this->autoSetToolboxInfo();
    }
    $this->autoSetProperties();
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractToolboxInfoTemplateVars();
    parent::initTemplateVars($vars);
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

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}