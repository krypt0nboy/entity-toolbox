<?php

/**
 * Class OperationsValueBuilderNotFieldable
 */
class EntityToolboxInfoOperationsBuilderFieldable extends EntityToolboxInfoOperationsBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'required_operations' => array(
        'publish'   => array(
          'handler'   => 'EntityToolboxOperationsPublish',
          'provision' => array(
            'menu' => TRUE
          )
        ),
        'unpublish' => array(
          'handler'   => 'EntityToolboxOperationsUnpublish',
          'provision' => array(
            'menu' => TRUE
          )
        ),
      )
    ), $args);
    parent::__construct($args);
  }
}