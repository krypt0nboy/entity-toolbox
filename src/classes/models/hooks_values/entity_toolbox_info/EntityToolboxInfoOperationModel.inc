<?php

/**
 * Class EntityToolboxInfoOperationModel
 */
class EntityToolboxInfoOperationModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'structure' => array(
        'handler'   => array(
          'type'    => 'string',
          'method'  => 'buildHandler',
        ),
        'provision' => array(
          'type'   => 'array',
          'method' => 'buildProvision',
        ),
      )
    ), $args);
    parent::__construct($args);
  }
}