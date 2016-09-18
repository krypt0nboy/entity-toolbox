<?php

/**
 * Class EntityInfoBuilder
 *
 * Base build class for hook_entity_info().
 */
class EntityInfoBuilder extends EntityToolboxDependentHookBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'                 => 'entity_info',
      'key_builders_classes' => array(
        'admin ui'      => 'AdminUIBuilder',
        'operations ui' => 'OperationsUiBuilder'
      )
    ), $args);
    parent::__construct($args);
  }

  /**
   * @return array
   */
  protected function buildAdminUi() {
    return $this->getKeyBuilder('admin ui')->build();
  }

  /**
   * @return mixed
   */
  protected function buildEntityKeys() {
    return $this->toolboxInfo['keys'];
  }

  protected function buildInlineEntityForm() {

  }

  /**
   * @return array
   */
  protected function buildOperationsUi() {
    return $this->getKeyBuilder('operations ui')->build();
  }
}