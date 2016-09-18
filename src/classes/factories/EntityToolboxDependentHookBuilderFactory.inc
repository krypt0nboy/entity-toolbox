<?php

/**
 * Class EntityToolboxDependentHookBuilderFactory
 */
class EntityToolboxDependentHookBuilderFactory extends EntityDependentHookBuilderFactory {
  /**
   * @var array $toolboxInfo
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(
      array(
        'instance_args' => array(
          'entity_type' => $args['entity_type']
        )
      )
    );
    parent::__construct($args);
  }

  /**
   *
   */
  protected function postSetEntityType() {
    if (!empty($this->constructArgs['toolbox_info'])) {
      $this->__set('toolbox_info', $this->constructArgs['toolbox_info']);
    }
    else {
      $this->__set('toolbox_info', entity_toolbox_get_info($this->entityType));
    }
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
   *
   */
  protected function postSetToolboxInfo() {
    $this->__set('fieldable', $this->toolboxInfo['fieldable']);
  }
}