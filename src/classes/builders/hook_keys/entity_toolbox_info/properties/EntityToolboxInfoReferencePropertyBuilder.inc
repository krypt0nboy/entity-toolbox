<?php

/**
 * Class EntityToolboxInfoReferencePropertyBuilder
 */
class EntityToolboxInfoReferencePropertyBuilder extends EntityToolboxInfoPropertyBuilder {
  use ReferenceDependentTraits, ReferenceDependentBuilderTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'key_builders_classes' => array(
        'schemas_fields_name' => 'EntityToolboxInfoReferencePropertySchemasFieldsNameBuilder'
      )
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractReferenceInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /**
   * Extracts the reference type.
   *
   * @return null|string
   */
  protected function extractReference() {
    $rawReference = !empty($this->rawPropertyInfo['reference']) ? $this->rawPropertyInfo['reference'] : NULL;
    if (is_null($rawReference)) {
      $reference = $this->getPropertyInstance()->getDefaultReference();
      $reference = $this->processValueTemplate($reference);

      return $reference;
    }
    else {
      return $rawReference;
    }
  }

  /** {{@inheritdoc}} */
  protected function postSetReference() {
    $this->__set('reference_info', $this->entityGetInfo($this->reference));
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'reference'      => $this->reference,
      'reference_info' => $this->referenceInfo,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  /** {{@inheritdoc}} */
  protected function buildReference() {
    return $this->reference;
  }

  /**
   * Builds "self_numeric_value".
   */
  protected function buildSelfNumericProperty() {

  }
}