<?php

/**
 * Class OperationsBuilderNotFieldable
 */
class EntityToolboxInfoOperationsBuilderNotFieldable extends EntityToolboxInfoOperationsBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'required_operations' => array(
        'manage_fields' => array(
          'handler'   => 'EntityToolboxOperationsManageFields',
          'provision' => array(
            'menu' => TRUE
          )
        ),
        'export'        => array(
          'handler'   => 'EntityToolboxOperationsExport',
          'provision' => array(
            'menu' => TRUE
          )
        ),
      )
    ), $args);
    parent::__construct($args);
  }
}