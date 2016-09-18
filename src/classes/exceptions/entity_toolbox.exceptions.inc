<?php

/**
 * Class EntityToolboxException
 */
class EntityToolboxException extends Exception {
  /**
   * @var string $template
   *   The message unprocessed template.
   *   (Eg : "Cannot instanciate %class%").
   */
  protected $template;

  /**
   * @var string[] $variables
   *   An array of string to replace matching tokens in the message.
   */
  protected $variables;

  /**
   * EntityToolboxException constructor.
   * @param string          $template
   * @param int             $code
   * @param array           $variables
   * @param null|\Exception $previous
   */
  public function __construct($template = "", $code = 0, $variables = array(), Exception $previous = NULL) {
    $this->template = $template;
    parent::__construct($template, $code, $previous);
    $this->message = string_template_process($this->template, $variables);
  }
}

/**
 * Class MissingEntityTypeException
 */
class MissingEntityTypeException extends EntityToolboxException {
  /**
   * MissingEntityTypeException constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Cannot create an instance of %class% without a specified entity type.";
    parent::__construct($template, 101, $variables, $previous);
  }
}

/**
 * Class MissingRawToolboxInfoException
 */
class ToolboxInfoNotProvidedException extends EntityToolboxException {
  /**
   * MissingRawToolboxInfoException constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Toolbox info not provided.";
    parent::__construct($template, 102, $variables, $previous);
  }
}

/**
 * Class MissingRawInfoException
 */
class MissingRawInfoException extends EntityToolboxException {
  /**
   * MissingRawInfoException constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Raw hook info not provided.";
    parent::__construct($template, 103, $variables, $previous);
  }
}

/**
 * Class HookNameNotProvided
 */
class HookNameNotProvided extends EntityToolboxException {
  /**
   * HookNameNotProvided constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Hook name not provided.";
    parent::__construct($template, 104, $variables, $previous);
  }
}

/**
 * Class ExtractMethodMissing
 */
class ExtractMethodMissing extends EntityToolboxException {
  /**
   * ExtractMethodMissing constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Extract method %method% does not exists.";
    parent::__construct($template, 105, $variables, $previous);
  }
}

/**
 * Class ProcessMethodMissing
 */
class ProcessMethodMissing extends EntityToolboxException {
  /**
   * ExtractMethodMissing constructor.
   */
  public function __construct(array $variables = array(), Exception $previous = NULL) {
    $template = "Process method %method% does not exists.";
    parent::__construct($template, 105, $variables, $previous);
  }
}

/**
 * Class InfoNotSet
 */
class InfoNotSet extends EntityToolboxException {
  /**
   * InfoNotSet constructor.
   */
  public function __construct(array $variables = array(), $previous = NULL) {
    $template = "Cannot extract info. Info is not set.";
    parent::__construct($template, 106, $variables, $previous);
  }
}