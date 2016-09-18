<?php

/**
 * Class EntityOperationsInfoOperationModel
 */
class EntityOperationInfoOperationModel extends EntityOperationInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'structure' => array(
        'handler'   => array(
          'type'    => 'string',
          'default' => 'EntityToolboxOperations%toolbox_info_operations_labels_label%',
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